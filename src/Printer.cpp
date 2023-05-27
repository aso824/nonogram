#include "Printer.h"

void Nonogram::Printer::print(Nonogram *nonogram, Grid *grid) {
    if (!nonogram && !grid) {
        throw std::invalid_argument("Expected nonogram and/or grid, nothing given");
    }

    pair<unsigned short, unsigned short> legendSize;

    if (nonogram) {
        // Calculate legend size
        legendSize.first = this->maxLength(nonogram->getRows());
        legendSize.second = this->maxLength(nonogram->getColumns());

        // Print top legend
        for (int i = legendSize.second - 1; i >= 0; i--) {
            spaces(legendSize.first * 2 + 2);

            for (auto &column: nonogram->getColumns()) {
                int index = column.size() - i - 1;

                if (index < 0) {
                    cout << "    ";
                } else {
                    cout << column.at(index) << "   ";
                }
            }

            cout << endl;
        }
    }

    // Print rows
    unsigned short rowCount = nonogram ? nonogram->getRows().size() : grid->size();

    for (int i = 0; i < rowCount; i++) {
        if (nonogram) {
            // Print row legend
            auto row = nonogram->getRows().at(i);

            for (int j = legendSize.first; j >= 0; j--) {
                int index = row.size() - j - 1;

                if (index < 0) {
                    cout << "  ";
                } else {
                    cout << row.at(index) << " ";
                }
            }
        }

        if (grid) {
            // Print row values
            auto row = grid->horizontal(i);

            for (auto cell: row) {
                if (cell) {
                    cout << "■   ";
                } else {
                    cout << "    ";
                }
            }
        }

        cout << endl;
    }
}

unsigned short Nonogram::Printer::maxLength(vector<Line> value) {
    unsigned short result = 0;

    for (auto &it: value) {
        for (auto &it2: value) {
            if (it2.size() > result) {
                result = it2.size();
            }
        }
    }

    return result;
}

void Nonogram::Printer::spaces(unsigned short amount) {
    while (amount-- > 0) {
        cout << " ";
    }
}
