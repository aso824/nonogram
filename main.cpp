#include <iostream>
#include "src/Nonogram.h"
#include "src/Loader/FileLoader.h"
#include "src/Printer.h"

using namespace std;

int main() {
    Nonogram::FileLoader loader;
    Nonogram::Nonogram simple = loader.load("data/simple.txt");

    Nonogram::Grid solution(5);
    solution.set(2, 0, true);
    solution.set(1, 1, true);
    solution.set(3, 1, true);
    solution.set(0, 2, true);
    solution.set(2, 2, true);
    solution.set(4, 2, true);
    solution.set(1, 3, true);
    solution.set(3, 3, true);
    solution.set(2, 4, true);

    Nonogram::Printer printer;
    printer.print(&simple, &solution);

    std::cout << "Errors: " << simple.verify(solution) << std::endl;

    return 0;
}
