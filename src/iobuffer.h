#pragma once

#include <iostream>

class Reader {
public:
    class UnexpectedEOF : public std::exception {};

    Reader(std::istream& istream);

    std::string Read(size_t len);

private:
    std::istream& istream_;
    std::string buffer_;
};


class Writer {
    Writer() = default;

    explicit Writer(std::ostream& ostream);

    void Write(const std::string& str);

    void Flush();

private:
    std::ostream* ostream_ = nullptr;
    unsigned char buffer_ = 0;
    size_t buffered_ = 0;
};
