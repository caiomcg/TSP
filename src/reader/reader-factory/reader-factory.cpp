#include "reader-factory.h"

#include <fstream>

ReaderFactory::ReaderFactory() {}
ReaderFactory::~ReaderFactory() {}

std::unique_ptr<Reader> ReaderFactory::createReader(const std::string& file_path) const {
    std::fstream file{file_path, std::ios::in};

    if (!file.is_open()) {
        throw std::runtime_error("could not open the desired file");
    }

    unsigned count = 0;
    std::string line;

    while (count++ < 3) {
        getline(file, line);
    }

    if (line == "EDGE_WEIGHT_SECTION")  return std::make_unique<EdgeWeightReader>(file_path);
    if (line == "DISPLAY_DATA_SECTION") return std::make_unique<DisplayDataReader>(file_path);

    throw std::runtime_error("invalid data type");
}
