#ifndef NONOGRAM_HILLCLIMB_H
#define NONOGRAM_HILLCLIMB_H

#include <vector>

#include "Heuristic.h"
#include "../Grid.h"

namespace Nonogram {
    class Hillclimb: public Heuristic {
        public:
            Hillclimb(): Heuristic() {}
            HeuristicResult solve(Nonogram &nonogram) override;

        private:
            std::unique_ptr<std::vector<Grid>> permute(Grid grid);
    };
}


#endif //NONOGRAM_HILLCLIMB_H
