#include "calculate.hpp"

namespace Utility {

int HammingDistance(const char* first, const char* second, size_t length) {
    auto result = 0;

    for (auto i = 0; i < length; i++) {
       result += __builtin_popcount(first[i] ^ second[i]);
    }

    return result;
}

}
