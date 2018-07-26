#include <string.h>
#include "match.hpp"

#include <iostream>

namespace Utility {

static const char *_patterns[] = {
    " a ", " the ", " is ", " of ", " at ",
    " on ", "'s", "oo", "ng", "'ve",
    "'m", " that ", " party "
};
static constexpr size_t _psizes[] = {
    3, 5, 4, 4, 4,
    4, 2, 2, 2, 3,
    2, 6, 7
};

static constexpr size_t _plen = sizeof(_patterns) / sizeof(*_patterns);

static bool _bytecmp(const uint8_t *start, const uint8_t *pattern, size_t plen) {
    while (--plen >= 0 && start[plen] == pattern[plen]);
    return plen == -1;
}

bool IsText(std::vector<uint8_t> bytes, size_t tolerance) {
    const auto size = bytes.size();
    const auto data = bytes.data();
    auto score = 0;

    for (auto i = 0; i < size; i++) {
        const auto byte = &data[i];
        for (auto j = 0; j < _plen; j++) {
            auto plen = _psizes[j];

            // if first byte doesn't match then there is no need to do a full comparison
            if (*byte != *_patterns[j]) {
                continue;
            }

            // first byte matches, so try to do a full comparison
            if ((i + plen) < size && _bytecmp(byte, reinterpret_cast<const uint8_t *>(_patterns[j]), plen)) {
                score++;
            }
        }
    }

    return score > tolerance;
}

}
