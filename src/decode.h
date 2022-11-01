#pragma once

#include "trie.h"
#include <vector>
#include <string>

class Decoder {
public:
    explicit Decoder(std::vector<std::pair<std::string, uint32_t>> codes);

    bool AddBit();

    uint32_t Get_Value();

private:
    TrieNode* root_;
    TrieNode* current_node_;
};
