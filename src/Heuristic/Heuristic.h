#ifndef NONOGRAM_HEURISTIC_H
#define NONOGRAM_HEURISTIC_H

#include <random>
#include <vector>
#include <utility>
#include <string>

#include "../Nonogram.h"
#include "../Grid.h"

namespace Nonogram {
    struct HeuristicResult {
        Grid solution;
        unsigned short result;
        std::vector<std::pair<int, std::string>> history;
    };

    class Heuristic {
        public:
            Heuristic() {
                this->rgen = std::mt19937(this->rd());
            }

            virtual ~Heuristic() = default;

            virtual HeuristicResult solve(Nonogram &nonogram) = 0;

        protected:
            std::random_device rd;
            std::mt19937 rgen;
    };

} // Nonogram

#endif //NONOGRAM_HEURISTIC_H
