#include <algorithm>
#include "encode.h"
#include <set>
#include <vector>

void Encoder::AddChar(uint32_t c) {
    ++freq_count_[c];
}

void TrieDfs(TrieNode* node, std::vector<std::pair<uint32_t, std::string>>& non_canonical_codes,
             std::string& current_code) {
    if (node->IsLeaf()) {
        non_canonical_codes.emplace_back(node->val, current_code);
        return;
    }
    if (node->child0 != nullptr) {
        current_code.push_back('0');
        TrieDfs(node->child0, non_canonical_codes, current_code);
        current_code.pop_back();
    }
    if (node->child1 != nullptr) {
        current_code.push_back('1');
        TrieDfs(node->child1, non_canonical_codes, current_code);
        current_code.pop_back();
    }
}

bool CanonicalHuffmanComparator(const std::pair<uint32_t, std::string>& lhs,
                                const std::pair<uint32_t, std::string>& rhs) {
    if (lhs.second.size() != rhs.second.size()) {
        return lhs.second.size() < rhs.second.size();
    }
    return lhs.second < rhs.second;
}

std::unordered_map<uint32_t, std::string> MakeCanonicalCodes(
    std::vector<std::pair<uint32_t, std::string>>& non_canonical_codes) {
    std::sort(non_canonical_codes.begin(), non_canonical_codes.end(), CanonicalHuffmanComparator);

    std::string current_code;
    std::unordered_map<uint32_t, std::string> canonical_codes;
    for (const auto& [val, non_canonical_code] : non_canonical_codes) {
        if (!current_code.empty()) {
            size_t pos = current_code.size() - 1;
            while (current_code[pos] != '0') {
                current_code[pos] = '0';
                pos--;
            }
        }
        while (current_code.size() < non_canonical_code.size()) {
            current_code.push_back('0');
        }
        canonical_codes[val] = current_code;
    }
    return canonical_codes;
}

std::unordered_map<uint32_t, std::string> Encoder::Encode() {
    std::unordered_map<uint32_t, uint32_t> child0;
    std::unordered_map<uint32_t, uint32_t> child1;

    std::set<TrieNode*> queue;
    for (auto [c, cnt] : freq_count_) {
        queue.insert(new TrieNode(c, cnt));
    }

    while (queue.size() > 1) {
        auto node1 = *queue.begin();
        queue.erase(queue.begin());
        auto node2 = *queue.begin();
        queue.erase(queue.begin());
        auto merged_node = new TrieNode(std::min(node1->val, node2->val), node1->freq + node2->freq);
        merged_node->child0 = node1;
        merged_node->child1 = node2;
        queue.insert(merged_node);
    }

    std::vector<std::pair<uint32_t, std::string>> non_canonical_codes;
    std::string current_code;
    TrieDfs(*queue.begin(), non_canonical_codes, current_code);
    codes_ = MakeCanonicalCodes(non_canonical_codes);
    return codes_;
}
