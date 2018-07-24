#ifndef XOR_HPP
#define XOR_HPP

#include <vector>

namespace Utility {

std::vector<uint8_t> FixedXor(const uint8_t* arg1, size_t arg1len, const uint8_t* arg2, size_t arg2len);

}

#endif