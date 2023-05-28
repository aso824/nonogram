#ifndef NONOGRAM_GRID_H
#define NONOGRAM_GRID_H

#include <vector>
#include <memory>
#include <random>

typedef std::vector<std::vector<bool>> vec2d;

namespace Nonogram {
    class Grid {
        private:
            std::unique_ptr<vec2d> values;
            unsigned short _size;

        public:
            Grid(unsigned short size);
            Grid(const vec2d &values);
            Grid(const Grid &from);

            Grid& operator=(const Grid& from);

            bool at(unsigned short x, unsigned short y);
            void set(unsigned short x, unsigned short y, bool value);
            bool flip(unsigned short x, unsigned short y);

            std::vector<bool> vertical(unsigned short index);
            std::vector<bool> horizontal(unsigned short index);

            unsigned short size() const { return this->_size; }

            static Grid random(unsigned short size, std::mt19937 rgen);
    };
}

#endif //NONOGRAM_GRID_H
