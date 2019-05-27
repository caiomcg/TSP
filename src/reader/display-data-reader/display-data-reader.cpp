#include "display-data-reader.h"

#include <iostream>

DisplayDataReader::DisplayDataReader(const std::string& file_path) : Reader(file_path) {}
DisplayDataReader::~DisplayDataReader() {}

void DisplayDataReader::prepare() {
    std::clog << "Preparing display data section" << std::endl;
}

void DisplayDataReader::process() {
    std::regex line_regex(R"(\d+( )+(\d+\.\d+)( )+(\d+\.\d+))");
    std::clog << "Processing " << this->file_path_ << std::endl;
}

unsigned* DisplayDataReader::getAdjacencyMatrix() {
    return nullptr;
}

int DisplayDataReader::getAdjacencyMatrixSize() {
    return -1;
}
