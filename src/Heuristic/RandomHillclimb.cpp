#include "RandomHillclimb.h"

namespace Nonogram {
    HeuristicResult RandomHillclimb::solve(Nonogram &nonogram) {
        const size_t MAX_ITERATIONS = 50000;

        Grid solution = Grid::random(nonogram.size(), this->rgen);
        unsigned int iterations = 0;
        unsigned short errors = nonogram.verify(solution);

        std::vector<std::pair<int, std::string>> history;
        history.push_back(std::make_pair<int, std::string>(errors, solution.hash()));

        while (++iterations < MAX_ITERATIONS) {
            Grid modified = this->randomModify(solution);
            unsigned short newErrors = nonogram.verify(modified);

            if (newErrors < errors) {
                solution = modified;
                errors = newErrors;
                history.push_back(std::make_pair<int, std::string>(errors, solution.hash()));
            }

            if (newErrors == 0) {
                break;
            }
        }

        return { solution, errors, history };
    }

    Grid RandomHillclimb::randomModify(Grid solution) {
        std::uniform_int_distribution<int> distr(0, solution.size() - 1);

        int x = distr(this->rgen);
        int y = distr(this->rgen);

        solution.set(x, y, !solution.at(x, y));

        return solution;
    }
} // Nonogram