#include "decode.h"

Decoder::Decoder(const std::vector<std::pair<std::string, uint32_t>>& codes) {
    root_ = new TrieNode();
    for (auto [seq, val] : codes) {
        AddCode(root_, seq, val);
    }
}

bool Decoder::AddBit(bool bit) {
    if (!bit) {
        if (current_node_->child0 == nullptr) {
            throw DecoderError();
        }
        current_node_ = current_node_->child0;
    } else {
        if (current_node_->child1 == nullptr) {
            throw DecoderError();
        }
        current_node_ = current_node_->child1;
    }
    return current_node_->IsLeaf();
}

uint32_t Decoder::GetValue() {
    uint32_t val = current_node_->val;
    current_node_ = root_;
    return val;
}

Decoder::~Decoder() {
    delete root_;
    delete current_node_;
}
