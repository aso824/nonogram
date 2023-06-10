#include "Tabu.h"

namespace Nonogram {
    HeuristicResult Tabu::solve(Nonogram &nonogram) {
        std::list<std::pair<int, std::string>> tabu;
        std::vector<std::pair<int, std::string>> history;

        auto last = Grid::random(nonogram.size(), this->rgen);
        tabu.push_back(std::make_pair<int, std::string>(nonogram.verify(last), last.hash()));

        auto best = tabu.back();

        for (size_t i = 0; i < this->iterations; i++) {
            auto neighbours = this->permute(last);
            std::vector<Grid> newNeighbours;

            for (auto& n: *neighbours) {
                auto hash = n.hash();

                bool exist = false;
                for (auto& t: tabu) {
                    if (t.second == hash) {
                        exist = true;
                        break;
                    }
                }

                if (!exist) {
                    newNeighbours.push_back(n);
                }
            }

            if (newNeighbours.empty()) {
                // Tail
                break;
            }

            auto bestNeigh = newNeighbours.at(0);
            auto bestNeighScore = nonogram.verify(bestNeigh);

            for (size_t j = 1; j < newNeighbours.size(); j++) {
                auto n = newNeighbours.at(j);
                auto score = nonogram.verify(n);

                if (score < bestNeighScore) {
                    bestNeigh = n;
                    bestNeighScore = score;
                }
            }

            auto neighHash = bestNeigh.hash();

            tabu.push_back(std::make_pair<int, std::string>(bestNeighScore, std::string(neighHash)));
            history.push_back(std::make_pair<int, std::string>(bestNeighScore, std::string(neighHash)));

            if (bestNeighScore < best.first) {
                best = tabu.back();
            }

            // Found solution
            if (bestNeighScore == 0) {
                break;
            }

            last = bestNeigh;

            // Tabu size exceeded, remove oldest one
            if (tabu.size() > this->tabu_size) {
                tabu.pop_front();
            }
        }

        return {
            Grid::from_hash(best.second, nonogram.size()),
            static_cast<unsigned short>(best.first),
            history
        };
    }

    std::unique_ptr<std::vector<Grid>> Tabu::permute(Grid grid) {
        std::unique_ptr<std::vector<Grid>> result = std::make_unique<std::vector<Grid>>();

        for (size_t x = 0; x < grid.size(); x++) {
            for (size_t y = 0; y < grid.size(); y++) {
                auto next = grid;

                next.flip(x, y);

                result->push_back(next);
            }
        }

        return result;
    }
} // Nonogram