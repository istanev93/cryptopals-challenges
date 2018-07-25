#include "xor.hpp"

namespace Utility {

std::vector<uint8_t> FixedXor(const uint8_t* arg1, size_t arg1len, const uint8_t* arg2, size_t arg2len) {
    std::vector<uint8_t> result;
    result.reserve(arg1len);

    for (auto i = 0; i < arg1len; i++) {
        result.push_back(arg1[i] ^ arg2[i]);
    }

    return result;
}

std::vector<uint8_t> SingleXor(const uint8_t* arg, size_t length, const uint8_t ch) {
    std::vector<uint8_t> result;
    result.reserve(length);

    for (auto i = 0; i < length; i++) {
        result.push_back(arg[i] ^ ch);
    }

    return result;
}

}