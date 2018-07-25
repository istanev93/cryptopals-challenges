#include "convert.hpp"

namespace Utility {

static const uint8_t _base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const uint8_t _mask = 0b11111100;
static const uint32_t _shift_amount = __builtin_popcount(_mask);

static const uint8_t _hexmap[] = "0123456789ABCDEF";

static std::string padding(size_t length) {
    auto rem = length % 3;
    return std::string(rem == 1 ? "=" : rem == 2 ? "==" : "");
}

std::string ToBase64(const uint8_t* bytes, size_t length) {
    if (length == 0) {
        return std::string("");
    }

    if (length < 3) {
        return std::string(1, _base64_table[bytes[0] & _mask]) + padding(length);
    }

    std::string result("");
    for (auto i = 0; i < length; i += 3) {
        auto byte1 = (bytes[i] & 0b11111100) >> 2;
        auto byte2 = ((bytes[i] & 0b00000011) << 4) | ((bytes[i + 1] & 0b11110000) >> 4);
        auto byte3 = ((bytes[i + 1] & 0b00001111) << 2) | ((bytes[i + 2] & 0b11000000) >> 6);
        auto byte4 = bytes[i + 2] & 0b00111111;

        result += std::string(1, _base64_table[byte1])
            + std::string(1, _base64_table[byte2])
            + std::string(1, _base64_table[byte3])
            + std::string(1, _base64_table[byte4]);
    }

    result += padding(length);
    return result;
}

std::string ToHex(const uint8_t* bytes, size_t length) {
    std::string s(length * 2, ' ');
    for (int i = 0; i < length; i++) {
        s[2 * i] = _hexmap[(bytes[i] & 0xF0) >> 4];
        s[2 * i + 1] = _hexmap[bytes[i] & 0x0F];
    }
    return s;
}

}