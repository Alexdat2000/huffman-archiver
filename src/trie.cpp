#include "trie.h"
#include <tuple>

TrieNode::TrieNode(uint32_t val, uint64_t freq) : val(val), freq(freq) {
}

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

void AddCode(TrieNode* node, const std::string& word, uint32_t val) {
    for (char c : word) {
        if (c == '0') {
            if (node->child0 == nullptr) {
                node->child0 = new TrieNode();
            }
            node = node->child0;
        } else {
            if (node->child1 == nullptr) {
                node->child1 = new TrieNode();
            }
            node = node->child1;
        }
    }
    node->val = val;
}
