#include "Nonogram.h"

Nonogram::Nonogram::Nonogram(std::vector<Line> rows, std::vector<Line> columns): rows(rows), columns(columns) {
    if (rows.size() != columns.size()) {
        throw std::invalid_argument("Nonogram must be square");
    }

    for (auto &line: rows) {
        if (line.empty()) {
            throw std::invalid_argument("Row cannot be empty");
        }
    }

    for (auto &line: columns) {
        if (line.empty()) {
            throw std::invalid_argument("Column cannot be empty");
        }
    }
}

unsigned short Nonogram::Nonogram::verify(Grid& solution) {
    if (solution.size() != this->rows.size()) {
        throw std::invalid_argument("Grid sizes are not equal - got " + std::to_string(solution.size()) + ", expected " + std::to_string(this->rows.size()));
    }

    unsigned short errors = 0;

    // Rows
    for (unsigned short i = 0; i < solution.size(); i++) {
        auto row = bitsToLine(solution.horizontal(i));

        if (this->rows.at(i) != row) {
            errors++;
        }
    }

    // Columns
    for (unsigned short i = 0; i < solution.size(); i++) {
        auto row = bitsToLine(solution.vertical(i));

        if (this->columns.at(i) != row) {
            errors++;
        }
    }

    return errors;
}

Line Nonogram::Nonogram::bitsToLine(std::vector<bool> bits) {
    Line result;

    unsigned short counter = 0;

    for (auto cell: bits) {
        if (!cell) {
            if (counter > 0) {
                result.push_back(counter);
            }

            counter = 0;
        } else {
            counter++;
        }
    }

    if (counter > 0) {
        result.push_back(counter);
    }

    return result;
}
