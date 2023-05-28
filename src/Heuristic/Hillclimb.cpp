#include "Hillclimb.h"

Nonogram::HeuristicResult Nonogram::Hillclimb::solve(Nonogram &nonogram) {
    const size_t MAX_ITERATIONS = 1000;

    Grid solution = Grid::random(nonogram.size(), this->rgen);
    unsigned int iterations = 0;
    unsigned short errors = nonogram.verify(solution);

    while (++iterations < MAX_ITERATIONS) {
        auto neighbours = this->permute(solution);
        bool changed = false;

        for (auto& candidate: (*neighbours)) {
            unsigned short newErrors = nonogram.verify(candidate);

            if (newErrors < errors) {
                solution = candidate;
                errors = newErrors;
                changed = true;
            }

            if (newErrors == 0) {
                break;
            }
        }

        if (!changed) {
            // Local max reached
            break;
        }
    }

    return { solution, iterations, errors };
}

std::unique_ptr<std::vector<Nonogram::Grid>> Nonogram::Hillclimb::permute(Grid grid) {
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
