#pragma once

#include <cstdint>

struct TrieNode {
    uint32_t val = 0;
    uint64_t freq = 0;

    TrieNode* child0 = nullptr;
    TrieNode* child1 = nullptr;

    TrieNode() = default;

    explicit TrieNode(uint32_t val, uint64_t freq);

    ~TrieNode();

    bool operator<(const TrieNode* rhs);

    bool IsLeaf() const;
};
