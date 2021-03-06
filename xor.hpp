#ifndef XOR_HPP
#define XOR_HPP

#include <vector>

namespace Utility {

std::vector<uint8_t> FixedXor(const uint8_t* arg1, size_t arg1len, const uint8_t* arg2, size_t arg2len);
std::vector<uint8_t> SingleXor(const uint8_t* arg, size_t length, const uint8_t ch);
std::vector<uint8_t> RepeatingXor(const uint8_t* text, size_t tlen, const uint8_t* key, size_t klen);

}

#endif
