#include "convert.hpp"

namespace Utility {

static std::string padding(size_t length) {
    auto rem = length % 3;
    return std::string(rem == 1 ? "=" : rem == 2 ? "==" : "");
}

std::string HexToBase64(const uint8_t* hex, size_t length) {
    if (length == 0) {
        return std::string("");
    }

    if (length < 3) {
        return std::string(1, _base64_table[hex[0] & _mask]) + padding(length);
    }

    std::string result("");
    for (auto i = 0; i < length; i += 3) {
        auto byte1 = (hex[i] & 0b11111100) >> 2;
        auto byte2 = ((hex[i] & 0b00000011) << 4) | ((hex[i + 1] & 0b11110000) >> 4);
        auto byte3 = ((hex[i + 1] & 0b00001111) << 2) | ((hex[i + 2] & 0b11000000) >> 6);
        auto byte4 = hex[i + 2] & 0b00111111;

        result += std::string(1, _base64_table[byte1])
            + std::string(1, _base64_table[byte2])
            + std::string(1, _base64_table[byte3])
            + std::string(1, _base64_table[byte4]);
    }

    result += padding(length);
    return result;
}

}