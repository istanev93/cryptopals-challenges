#ifndef CONVERT_HPP
#define CONVERT_HPP

#include <string>

namespace Utility {

std::string ToBase64(const uint8_t* bytes, size_t length);
std::string ToHex(const uint8_t* bytes, size_t length);

}

#endif
