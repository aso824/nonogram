
#ifndef NONOGRAM_FILELOADER_H
#define NONOGRAM_FILELOADER_H

#include <fstream>
#include <vector>
#include <string>
#include <cstring>

#include "Loader.h"

namespace Nonogram {
    class FileLoader: public Loader {
        public:
            Nonogram load(const char* path);

        private:
            Line explode(char* line);
    };

} // Nonogram

#endif //NONOGRAM_FILELOADER_H
