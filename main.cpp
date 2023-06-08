#include <iostream>
#include <string>
#include <memory>
#include <map>

#include "src/Nonogram.h"
#include "src/Loader/FileLoader.h"
#include "src/Printer.h"
#include "src/Heuristic/Hillclimb.h"
#include "src/Heuristic/RandomHillclimb.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Usage: nonogram [file] [algorithm]" << endl;

        return 1;
    }

    string filename = argv[1];
    string algo = argv[2];
    map<string, string> flags;

    for (size_t i = 3; i < argc; i++) {
        string param = argv[i];

        if (param[0] != '-' || param[1] != '-') {
            continue;
        }

        param = param.substr(2);

        flags[param] = "";
    }

    Nonogram::FileLoader loader;
    Nonogram::Nonogram problem = loader.load(filename.c_str());

    unique_ptr<Nonogram::Heuristic> algorithm;

    if (algo == "hillclimb") {
        algorithm = make_unique<Nonogram::Hillclimb>();
    } else if (algo == "hillclimb_random") {
        algorithm = make_unique<Nonogram::RandomHillclimb>();
    } else {
        cout << "Unknown algorithm" << endl;

        return 1;
    }

    auto result = algorithm->solve(problem);

    Nonogram::Printer printer;
    printer.print(&problem, &result.solution);

    cout << "Errors: " << result.result << " in " << result.iterations << " iterations" << endl;
    cout << "Result hash: " << result.solution.hash() << endl;

    return 0;
}
