#include "trie.h"
#include <tuple>

TrieNode::TrieNode(uint32_t val, uint64_t freq) : val(val), freq(freq) {}

TrieNode::~TrieNode() {
    delete child0;
    delete child1;
}

bool TrieNode::operator<(const TrieNode* rhs) {
    return std::tie(freq, val) < std::tie(rhs->freq, rhs->val);
}
bool TrieNode::IsLeaf() const {
    return child0 == nullptr && child1 == nullptr;
}
