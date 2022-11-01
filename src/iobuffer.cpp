#include "iobuffer.h"

Reader::Reader(std::istream& istream, size_t block_size) : istream_(&istream), block_size_(block_size) {
}

bool
uint32_t Reader::Read() {
    while (bits_buffered_ < block_size_) {
        buffer_ <<= 8;
        char c;
        if (!(*istream_ >> c)) {
            break;
        }
        buffer_ += c;
    }
    uint32_t block = buffer_ >> (bits_buffered_ - block_size_);
    bits_buffered_ -= block_size_;
    buffer_ &= (1 << bits_buffered_);
    return block;
}
