#ifndef READER_READER_FACTORY_H
#define READER_READER_FACTORY_H

#include <memory>

#include "../edge-weight-reader/edge-weight-reader.h"
#include "../display-data-reader/display-data-reader.h"

class ReaderFactory final {
public:
    ReaderFactory();
    ~ReaderFactory();

    std::unique_ptr<Reader> createReader(const std::string& file_path) const;
};

#endif // define READER_READER_FACTORY_H
