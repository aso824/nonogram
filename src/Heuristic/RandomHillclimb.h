#ifndef NONOGRAM_RANDOMHILLCLIMB_H
#define NONOGRAM_RANDOMHILLCLIMB_H

#include "Heuristic.h"

namespace Nonogram {
    class RandomHillclimb: public Heuristic {
        public:
            RandomHillclimb(): Heuristic() {}
            HeuristicResult solve(Nonogram &nonogram) override;

        private:
            Grid randomModify(Grid solution);
    };

} // Nonogram

#endif //NONOGRAM_RANDOMHILLCLIMB_H
