#pragma once

#include "trie.h"
#include <vector>
#include <string>

class Decoder {
public:
    class DecoderError : public std::exception {};

    explicit Decoder(const std::vector<std::pair<std::string, uint32_t>>& codes);

    bool AddBit(bool bit);

    uint32_t GetValue();

    ~Decoder();

private:
    TrieNode* root_;
    TrieNode* current_node_;
};
