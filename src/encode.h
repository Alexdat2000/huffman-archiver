#pragma once

#include "trie.h"
#include <unordered_map>

class Encoder {
public:
    Encoder() = default;

    void AddChar(uint32_t c);

    std::unordered_map<uint32_t, std::string> Encode();

private:
    std::unordered_map<uint32_t, uint64_t> freq_count_{{256, 1}, {257, 1}, {258, 1}};
};
