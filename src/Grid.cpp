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

