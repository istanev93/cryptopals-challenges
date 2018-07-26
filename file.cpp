#include "file.hpp"

#include <map>
#include <fstream>

namespace Utility {

static std::map<int, uint8_t> _map {
    { '0', 0x00 },
    { '1', 0x01 },
    { '2', 0x02 },
    { '3', 0x03 },
    { '4', 0x04 },
    { '5', 0x05 },
    { '6', 0x06 },
    { '7', 0x07 },
    { '8', 0x08 },
    { '9', 0x09 },
    { 'a', 0x0A },
    { 'b', 0x0B },
    { 'c', 0x0C },
    { 'd', 0x0D },
    { 'e', 0x0E },
    { 'f', 0x0F }
};

std::vector<std::vector<uint8_t>> ReadKnownFile(const char *filename, const int linesz, const int nlines) {
    std::ifstream file (filename, std::ifstream::in);
    std::vector<std::vector<uint8_t>> lines;
    lines.reserve(nlines);

    for (auto i = 0; i < nlines && file.good(); i++) {
        std::vector<uint8_t> v;
        v.reserve(linesz / 2);

        uint8_t byte;
        do {
            auto ch = file.get();
            if (file.eof()) {
                break;
            }
            if (ch == '\n') {
                break;
            }

            auto ch2 = file.get();
            if (file.eof()) {
                break;
            }
            if (ch2 == '\n') {
                break;
            }

            byte = (_map[ch] << 4) | _map[ch2];

            v.push_back(byte);
        } while (true);

        lines.push_back(v);
    }

    return lines;
}

}
