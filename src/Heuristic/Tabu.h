#ifndef NONOGRAM_TABU_H
#define NONOGRAM_TABU_H

#include <list>
#include <vector>
#include <memory>
#include <algorithm>

#include "Heuristic.h"
#include "../Grid.h"

namespace Nonogram {
    class Tabu: public Heuristic {
        public:
            Tabu(): Heuristic() {}
            HeuristicResult solve(Nonogram& nonogram) override;

        private:
            const int tabu_size = 500;
            const int iterations = 2000;

            std::unique_ptr<std::vector<Grid>> permute(Grid grid);
    };

} // Nonogram

#endif //NONOGRAM_TABU_H
