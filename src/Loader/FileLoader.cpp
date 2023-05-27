#include "FileLoader.h"

namespace Nonogram {
    Nonogram FileLoader::load(const char *path) {
        std::fstream stream;
        stream.open(path, std::ios::in);

        if (!stream.good()) {
            throw std::invalid_argument("Cannot open file");
        }

        unsigned short size;
        stream >> size;

        std::vector<Line> rows;
        std::vector<Line> columns;
        std::string buf;

        for (unsigned short i = 0; i < size; i++) {
            stream >> buf;

            rows.push_back(this->explode(strdup(buf.c_str())));
        }

        for (unsigned short i = 0; i < size; i++) {
            stream >> buf;
            columns.push_back(this->explode(strdup(buf.c_str())));
        }

        stream.close();

        return { rows, columns };
    }

    Line FileLoader::explode(char* line) {
        Line result;

        char* p = strtok(line, ",");

        while (p != nullptr) {
            unsigned short value = std::strtoul(p, nullptr, 0);

            result.push_back(value);

            p = strtok(nullptr, ",");

            if (result.size() > 10) {
                exit(1);
            }
        }

        return result;
    }
} // Nonogram