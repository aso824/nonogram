#ifndef NONOGRAM_NONOGRAM_H
#define NONOGRAM_NONOGRAM_H

#include <vector>
#include <memory>
#include "Grid.h"

typedef std::vector<unsigned short> Line;

namespace Nonogram {
    class Nonogram {
        private:
            std::vector<Line> rows;
            std::vector<Line> columns;

        public:
            Nonogram(std::vector<Line> rows, std::vector<Line> columns);
            unsigned short verify(Grid& solution);

            std::vector<Line> getRows() { return this->rows; }
            std::vector<Line> getColumns() { return this->columns; }

            unsigned short size() { return this->rows.size(); }

        private:
            Line bitsToLine(std::vector<bool> bits);
    };

} // Nonogram

#endif //NONOGRAM_NONOGRAM_H
