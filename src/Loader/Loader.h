#ifndef NONOGRAM_LOADER_H
#define NONOGRAM_LOADER_H

#include "../Nonogram.h"

namespace Nonogram {
    class Loader {
        public:
            virtual Nonogram load(const char* input) = 0;
    };
}


#endif //NONOGRAM_LOADER_H
