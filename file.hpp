#ifndef FILE_HPP
#define FILE_HPP

#include <vector>
#include <string>

namespace Utility {

std::vector<std::vector<uint8_t>> ReadKnownFile(const char *filename, const int linesz, const int nlines);

}

#endif
