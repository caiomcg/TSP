#include "edge-weight-reader.h"

#include <iostream>

EdgeWeightReader::EdgeWeightReader(const std::string& file_path) : Reader(file_path) {}
EdgeWeightReader::~EdgeWeightReader() {}

void EdgeWeightReader::prepare() {
    std::clog << "Preparing edge..." << std::endl;
}
void EdgeWeightReader::process() {
    std::clog << "Processing " << this->file_path_ << std::endl;
}
