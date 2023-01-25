#include "iobuffer.h"

Reader::Reader(std::istream& istream) : istream_(istream) {
}

std::string Reader::Read(size_t len) {
    while (buffer_.size() < len) {
        char c;
        if (!(*istream_ >> c)) {
            throw UnexpectedEOF();
        }
        for (size_t i = 0; i < 8; ++i) {
            buffer_.push_back('0' + ((c >> (7 - i)) & 1));
        }
    }
    auto ans_substr = buffer_.substr(0, len);
    buffer_.erase(buffer_.begin(), buffer_.begin() + len);
    return ans_substr;
}

Writer::Writer(std::ostream& ostream): ostream_(&ostream) {
}

void Writer::Flush() {
    if (buffered_ == 8) {
        *ostream_ << buffer_;
        buffer_ = 0;
        buffered_ = 0;
    }
}

void Writer::Write(const std::string& str) {
    for (char c : str) {
        buffer_ = (buffer_ << 1) + (c - '0');
        ++buffered_;
        Flush();
    }
}
