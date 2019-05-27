#include "display-data-reader.h"

#include <iostream>

DisplayDataReader::DisplayDataReader(const std::string& file_path) : Reader(file_path) {}
DisplayDataReader::~DisplayDataReader() {}

void DisplayDataReader::prepare() {
    std::clog << "Preparing display..." << std::endl;
}
void DisplayDataReader::process() {
    std::clog << "Processing " << this->file_path_ << std::endl;
}
