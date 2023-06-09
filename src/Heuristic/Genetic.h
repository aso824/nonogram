#ifndef NONOGRAM_GENETIC_H
#define NONOGRAM_GENETIC_H

#include <vector>
#include <algorithm>

#include "Heuristic.h"
#include "../Grid.h"

namespace Nonogram {
    class Genetic: public Heuristic {
        public:
            Genetic(): Heuristic() {}
            HeuristicResult solve(Nonogram& nonogram) override;

        private:
            std::vector<int> selection(const std::vector<int>& pop_errors);
            std::pair<Grid, Grid> crossover(std::pair<Grid, Grid> pair);
            std::pair<int, Grid> best(std::vector<Grid>& solutions, Nonogram& nonogram);
            void randomModify(Grid& solution);

            const int pop_size = 200;
            const int iterations = 25;
            const double p_crossover = 0.4;
            const double p_mutation = 0.3;
    };

} // Nonogram

#endif //NONOGRAM_GENETIC_H
