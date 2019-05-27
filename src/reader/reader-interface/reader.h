#ifndef READER_READER_INTERFACE_READER_H
#define READER_READER_INTERFACE_READER_H

#include <string>

class Reader {
protected:
    std::string file_path_;
public:
    Reader(const std::string file_path);
    virtual ~Reader();

    virtual void prepare() noexcept(false) = 0;
    virtual void process() = 0;
};

#endif // define READER_READER_H
