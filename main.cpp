#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>

#include "file.hpp"
#include "convert.hpp"
#include "xor.hpp"
#include "match.hpp"
#include "calculate.hpp"

const int FILE_4_LINES = 327;
const int FILE_4_LINESZ = 60;
constexpr int FILE_4_SZ = FILE_4_LINES * FILE_4_LINESZ;

int main(int argc, char const *argv[]) {
    //
    // Challenge 1
    //
    uint8_t bytes[] = { 
        0x49, 0x27, 0x6d, 0x20, 0x6b, 0x69, 0x6c, 0x6c, 0x69, 
        0x6e, 0x67, 0x20, 0x79, 0x6f, 0x75, 0x72, 0x20, 0x62, 0x72, 0x61, 0x69, 
        0x6e, 0x20, 0x6c, 0x69, 0x6b, 0x65, 0x20, 0x61, 0x20, 0x70, 0x6f, 0x69, 
        0x73, 0x6f, 0x6e, 0x6f, 0x75, 0x73, 0x20, 0x6d, 0x75, 0x73, 0x68, 0x72,
        0x6f, 0x6f, 0x6d };
    // TODO: use vector overload
    std::cout << Utility::ToBase64(bytes, sizeof(bytes)) << std::endl;

    //
    // Challenge 2
    //
    uint8_t xor1[] = {
        0x1c, 0x01, 0x11, 0x00, 0x1f, 0x01, 0x01, 0x00, 0x06, 0x1a, 0x02, 0x4b,
        0x53, 0x53, 0x50, 0x09, 0x18, 0x1c
    };
    uint8_t xor2[] = {
        0x68, 0x69, 0x74, 0x20, 0x74, 0x68, 0x65, 0x20, 0x62, 0x75, 0x6c, 0x6c,
        0x27, 0x73, 0x20, 0x65, 0x79, 0x65
    };
    // TODO: use vector overload
    auto xor_vector = Utility::FixedXor(xor1, sizeof(xor1), xor2, sizeof(xor2));
    // TODO: use vector overeload
    std::cout << Utility::ToHex(xor_vector.data(), xor_vector.size()) << std::endl;
    
    //
    // Challenge 3
    //
    uint8_t single_str[] = { 
        0x1b, 0x37, 0x37, 0x33, 0x31, 0x36, 0x3f, 0x78, 0x15, 0x1b, 0x7f, 0x2b,
        0x78, 0x34, 0x31, 0x33, 0x3d, 0x78, 0x39, 0x78, 0x28, 0x37, 0x2d, 0x36,
        0x3c, 0x78, 0x37, 0x3e, 0x78, 0x3a, 0x39, 0x3b, 0x37, 0x36
    };

    for (auto i = 0; i < 256; i++) {
        // TODO: use vector overload
        auto res = Utility::SingleXor(single_str, sizeof(single_str), static_cast<uint8_t>(i));
        if (Utility::IsText(res, 4)) {
            std::cout << std::string(res.begin(), res.end()) << std::endl;
        }
    }

    //
    // Challenge 4
    //
    auto hashes = Utility::ReadKnownFile("4.txt", FILE_4_LINESZ, FILE_4_LINES);
    for (auto& hash : hashes) {
        for (auto i = 0; i < 256; i++) {
            auto res = Utility::SingleXor(hash.data(), hash.size(), i);
            if (Utility::IsText(res, 4)) {
                std::cout << std::string(res.begin(), res.end()) << std::endl;
            }
        }
    }

    //
    // Challenge 5
    //
    const char text[] = "Burning 'em, if you ain't quick and nimble\n"
        "I go crazy when I hear a cymbal";
    const char key[] = "ICE";
    auto res = Utility::RepeatingXor(reinterpret_cast<const uint8_t *>(text), sizeof(text) - 1, reinterpret_cast<const uint8_t *>(key), sizeof(key) - 1);
    std::cout << Utility::ToHex(res.data(), res.size()) << std::endl;

    const char other1[] = "Here is the opening stanza of an important work of the English language:";
    res = Utility::RepeatingXor(reinterpret_cast<const uint8_t *>(other1), sizeof(other1) - 1, reinterpret_cast<const uint8_t *>(key), sizeof(key) - 1);
    std::cout << Utility::ToHex(res.data(), res.size()) << std::endl;

    const char other2[] = "res = Utility::RepeatingXor(reinterpret_cast<const uint8_t *>(other2), sizeof(other2) - 1, reinterpret_cast<const uint8_t *>(key), sizeof(key) - 1);";
    res = Utility::RepeatingXor(reinterpret_cast<const uint8_t *>(other2), sizeof(other2) - 1, reinterpret_cast<const uint8_t *>(key), sizeof(key) - 1);
    std::cout << Utility::ToHex(res.data(), res.size()) << std::endl;

    const char other3[] = "istanev93@gmail.com";
    res = Utility::RepeatingXor(reinterpret_cast<const uint8_t *>(other3), sizeof(other3) - 1, reinterpret_cast<const uint8_t *>(key), sizeof(key) - 1);
    std::cout << Utility::ToHex(res.data(), res.size()) << std::endl;

    //
    // Challenge 6
    //
    const char s1[] = "this is a test";
    const char s2[] = "wokka wokka!!!";
    std::cout << Utility::HammingDistance(s1, s2, sizeof(s1)) << std::endl;

    auto file6 = Utility::ReadKnownFile("6.txt", 60, 64);
    std::vector<std::tuple<int, int>> distances;
    distances.reserve(file6.size());

    for (auto line = 0, keysz = 2; line < file6.size(); keysz++, line++) {
        auto text = file6[line];
        auto tlen = text.size();

        auto normalised = 0;
        auto blocks = text.size() / keysz;
        for (auto block = 0; block < blocks; block += 2) {
            auto first = text.data() + (block * keysz);
            auto second = text.data() + ((block + 1) * keysz);
            auto dist = Utility::HammingDistance(reinterpret_cast<const char*>(first), reinterpret_cast<const char*>(second), keysz);
            normalised += dist / keysz;
        }
        if (blocks != 0) {
            normalised /= blocks;
        }
        
        distances.push_back(std::make_tuple(normalised, keysz));
    }
    auto minv = std::min_element(distances.begin(), distances.end(), 
        [&](std::tuple<int, int> l, std::tuple<int, int> r) -> bool {
            return std::get<0>(l) < std::get<0>(r);
        });
    std::cout << std::get<1>(*(minv)) << std::endl;
    return 0;
}
