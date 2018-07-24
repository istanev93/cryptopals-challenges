#ifndef CONVERT_HPP
#define CONVERT_HPP

#include <string>

namespace Utility {

const uint8_t _base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const uint8_t _mask = 0b11111100;
const uint32_t _shift_amount = __builtin_popcount(_mask);

std::string HexToBase64(const uint8_t* hex, size_t length);

};

#endif
