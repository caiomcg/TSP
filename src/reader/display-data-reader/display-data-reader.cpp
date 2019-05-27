#include "display-data-reader.h"

#include <iostream>

DisplayDataReader::DisplayDataReader(const std::string& file_path) : Reader(file_path) {}
DisplayDataReader::~DisplayDataReader() {}

void DisplayDataReader::prepare() {
    std::clog << "Preparing display data section" << std::endl;
}

void DisplayDataReader::process() {
    std::regex line_regex(R"(\d+( )+(\d+\.\d+)( )+(\d+\.\d+))");
    this->fetchDimension(this->file_stream_);
    if (this->dimension_ == -1) throw std::runtime_error("invalid entry dimension");

    if (!this->allocateAdjacencyMatrixWith(this->dimension_ * this->dimension_)) {
        throw std::runtime_error("could not allocate the memory space");
    }

    std::clog << "Processing " << this->file_path_ << std::endl;
}
