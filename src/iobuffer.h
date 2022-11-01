#pragma once

#include <iostream>

class Reader {
public:
    Reader() = default;

    Reader(std::istream& istream, size_t block_size);

    uint32_t Read();

private:
    std::istream* istream_ = nullptr;
    uint32_t buffer_ = 0;
    size_t bits_buffered_ = 0;
    const size_t block_size_ = 0;
};
