#include "xor.hpp"

namespace Utility {

std::vector<uint8_t> FixedXor(const uint8_t* arg1, size_t arg1len, const uint8_t* arg2, size_t arg2len) {
    std::vector<uint8_t> result;

    for (auto i = 0; i < arg1len; i++) {
        result.push_back(arg1[i] ^ arg2[i]);
    }

    return result;
}

}