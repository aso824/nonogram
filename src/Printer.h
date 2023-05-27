#ifndef NONOGRAM_PRINTER_H
#define NONOGRAM_PRINTER_H

#include "Nonogram.h"

#include <iostream>
#include <utility>

using namespace std;

namespace Nonogram {
    class Printer {
        public:
            void print(Nonogram* nonogram = nullptr, Grid* grid = nullptr);

        private:
            unsigned short maxLength(vector<Line> value);
            void spaces(unsigned short amount);
    };
}

#endif //NONOGRAM_PRINTER_H
