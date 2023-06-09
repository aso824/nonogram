#include "Genetic.h"

namespace Nonogram {
    HeuristicResult Genetic::solve(Nonogram &nonogram) {
        std::vector<std::pair<int, std::string>> history;
        std::vector<Grid> population;

        for (size_t i = 0; i < this->pop_size; i++) {
            population.push_back(Grid::random(nonogram.size(), this->rgen));
        }

        std::sort(population.begin(), population.end(), [&](auto a, auto b) { return nonogram.verify(a) < nonogram.verify(b); });

        for (size_t iteration = 0; iteration < this->iterations; iteration++) {
            // Calculate errors for each solution
            std::vector<int> errors(this->pop_size);
            std::transform(population.begin(), population.end(), errors.begin(), [&](auto grid) { return nonogram.verify(grid); });

            // Selection - roulette; *indexes* of selected solutions
            auto selected = this->selection(errors);

            // Next generation
            std::vector<Grid> new_population;

            for (size_t i = 0; i < (this->pop_size - 1); i += 2) {
                // Create pairs
                std::pair<Grid, Grid> pair { population.at(selected.at(i)), population.at(selected.at(i + 1)) };

                // Random crossover
                std::uniform_real_distribution<double> distr(0.0, 1.0);

                if (distr(this->rgen) > this->p_crossover) {
                    pair = this->crossover(pair);
                }

                // Random mutation
                if (distr(this->rgen) > this->p_mutation) {
                    randomModify(pair.first);
                }

                if (distr(this->rgen) > this->p_mutation) {
                    randomModify(pair.second);
                }

                // Store new solutions
                new_population.push_back(pair.first);
                new_population.push_back(pair.second);
            }

            // Use new generation of solutions
            population = new_population;

            // Store history
            auto best = this->best(population, nonogram);

            history.push_back({ best.first, best.second.hash() });

            // Stop if solved
            if (best.first == 0) {
                break;
            }
        }

        // Sort by best
        std::sort(population.begin(), population.end(), [&](auto a, auto b) { return nonogram.verify(a) < nonogram.verify(b); });

        return { population.at(0), nonogram.verify(population.at(0)), history };
    }

    std::vector<int> Genetic::selection(const std::vector<int> &pop_errors) {
        std::uniform_int_distribution<int> distr(0, pop_errors.size() - 1);

        std::vector<int> result;

        while (result.size() < pop_errors.size()) {
            int a = distr(this->rgen);
            int b = distr(this->rgen);

            result.push_back(pop_errors[a] < pop_errors[b] ? a : b);
        }

        return result;
    }

    std::pair<Grid, Grid> Genetic::crossover(std::pair<Grid, Grid> pair) {
        auto size = pair.first.size();

        auto first = pair.first.binary();
        auto second = pair.second.binary();

        std::uniform_int_distribution<int> distr(0, first.size() - 1);
        int cut = distr(this->rgen);

        std::vector<bool> r_first(first.begin(), first.begin() + cut);
        r_first.insert(r_first.end(), second.begin() + cut, second.end());

        std::vector<bool> r_second(second.begin(), second.begin() + cut);
        r_second.insert(r_second.end(), first.begin() + cut, first.end());

        return { Grid(r_first, size), Grid(r_second, size) };
    }

    std::pair<int, Grid> Genetic::best(std::vector<Grid> &solutions, Nonogram& nonogram) {
        Grid* result = &solutions.at(0);
        int min_errors = nonogram.verify(solutions.at(0));

        for (auto &it: solutions) {
            int e = nonogram.verify(it);

            if (e < min_errors) {
                result = &it;
                min_errors = e;
            }
        }

        return { min_errors, *result };
    }

    void Genetic::randomModify(Grid &solution) {
        std::uniform_int_distribution<int> distr(0, solution.size() - 1);

        int x, y;

        do {
            x = distr(this->rgen);
            y = distr(this->rgen);
        } while (x == y);

        solution.set(x, y, !solution.at(x, y));
    }
} // Nonogram