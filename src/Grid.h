#ifndef NONOGRAM_GRID_H
#define NONOGRAM_GRID_H

#include <vector>
#include <memory>

typedef std::vector<std::vector<bool>> vec2d;

namespace Nonogram {
    class Grid {
        private:
            std::unique_ptr<vec2d> values;
            unsigned short _size;

        public:
            Grid(unsigned short size);
            Grid(const vec2d &values);

            bool at(unsigned short x, unsigned short y);
            void set(unsigned short x, unsigned short y, bool value);

            std::vector<bool> vertical(unsigned short index);
            std::vector<bool> horizontal(unsigned short index);



            unsigned short size() const { return this->_size; }
    };
}

#endif //NONOGRAM_GRID_H
