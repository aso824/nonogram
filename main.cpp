#include <iostream>
#include <memory>

#include "src/Nonogram.h"
#include "src/Loader/FileLoader.h"
#include "src/Printer.h"
#include "src/Heuristic/Hillclimb.h"
#include "src/Heuristic/RandomHillclimb.h"

using namespace std;

int main() {
    Nonogram::FileLoader loader;
    Nonogram::Nonogram problem = loader.load("data/simple.txt");

    const int algo = 0;
    unique_ptr<Nonogram::Heuristic> algorithm;

    switch (algo) {
        case 0: algorithm = make_unique<Nonogram::Hillclimb>(); break;
        case 1: algorithm = make_unique<Nonogram::RandomHillclimb>(); break;
    }

    auto result = algorithm->solve(problem);

    Nonogram::Printer printer;
    printer.print(&problem, &result.solution);

    cout << "Errors: " << result.result << " in " << result.iterations << " iterations" << endl;

    return 0;
}
