#include "Grid.h"

Nonogram::Grid::Grid(unsigned short size) {
    this->_size = size;
    this->values = std::make_unique<vec2d>();

    for (unsigned short i = 0; i < size; i++) {
        this->values->push_back(std::vector<bool>(size));
    }
}

Nonogram::Grid::Grid(const vec2d &values) {
    this->values = std::make_unique<vec2d>(values);
    this->_size = values.size();

    for (auto &row: values) {
        if (this->_size != row.size()) {
            throw std::invalid_argument("Grid must be square");
        }
    }
}

Nonogram::Grid::Grid(const Nonogram::Grid &from) {
    vec2d data;
    std::copy(from.values->begin(), from.values->end(), std::back_inserter(data));

    this->values = std::make_unique<vec2d>(data);
    this->_size = from.size();
}

Nonogram::Grid::Grid(const std::string hash, unsigned short size) {
    this->_size = size;
    this->values = std::make_unique<vec2d>();

    std::vector<bool> bits;

    for (const char& hex: hash) {
        uint8_t byte = 0;

        if (hex >= '0' && hex <= '9') {
            byte = hex - '0';
        }
        else if (hex >= 'A' && hex <= 'F') {
            byte = hex - 'A' + 10;
        }
        else if (hex >= 'a' && hex <= 'f') {
            byte = hex - 'a' + 10;
        }

        std::bitset<4> bs(byte);

        for (int i = 3; i >= 0; --i) {
            bits.push_back(bs[i]);
        }
    }

    std::vector<bool> line;

    for (auto bit: bits) {
        line.push_back(bit);

        if (line.size() == size) {
            this->values->push_back(line);
            line.clear();
        }
    }
}

Nonogram::Grid &Nonogram::Grid::operator=(const Nonogram::Grid &from) {
    vec2d data;
    std::copy(from.values->begin(), from.values->end(), std::back_inserter(data));

    this->values = std::make_unique<vec2d>(data);
    this->_size = from.size();

    return *this;
}

bool Nonogram::Grid::at(unsigned short x, unsigned short y) {
    if (x > this->_size || y > this->_size) {
        throw std::out_of_range("Out of bounds");
    }

    return this->values->at(y).at(x);
}

void Nonogram::Grid::set(unsigned short x, unsigned short y, bool value) {
    if (x > this->_size || y > this->_size) {
        throw std::out_of_range("Out of bounds");
    }

    this->values->at(y)[x] = value;
}

bool Nonogram::Grid::flip(unsigned short x, unsigned short y) {
    const bool value = !this->at(x, y);

    this->set(x, y, value);

    return value;
}

std::vector<bool> Nonogram::Grid::vertical(unsigned short index) {
    std::vector<bool> result;

    for (unsigned short i = 0; i < this->_size; i++) {
        result.push_back(this->at(index, i));
    }

    return result;
}

std::vector<bool> Nonogram::Grid::horizontal(unsigned short index) {
    return this->values->at(index);
}

Nonogram::Grid Nonogram::Grid::random(unsigned short size, std::mt19937 rgen) {
    vec2d values;

    std::uniform_int_distribution<int> dist(0, 1);

    for (unsigned short i = 0; i < size; i++) {
        std::vector<bool> row;

        for (unsigned short j = 0; j < size; j++) {
            row.push_back(dist(rgen));
        }

        values.push_back(row);
    }

    return { values };
}

std::string Nonogram::Grid::hash() {
    std::ostringstream oss;

    // Grid to single vector
    std::vector<bool> bits;
    for (auto &it: *values) {
        for (auto bit: it) {
            bits.push_back(bit);
        }
    }

    // Right pad zeroes
    for (size_t i = 0; i < (bits.size() % 4); i++) {
        bits.push_back(false);
    }

    // Convert each 4 cells into single hex character
    for (size_t i = 0; i < bits.size(); i += 4) {
        uint8_t byte = 0;

        for (size_t j = 0; j < 4; j++) {
            byte |= (bits[i + j] << (3 - j));
        }

        oss << std::hex << std::setw(1) << std::setfill('0') << (int) byte;
    }

    return oss.str();
}


