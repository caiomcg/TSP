#include "edge-weight-reader.h"

#include <iostream>

EdgeWeightReader::EdgeWeightReader(const std::string& file_path) : Reader(file_path), dimension_{-1} {}
EdgeWeightReader::~EdgeWeightReader() {
    if (this->adjacency_matrix_ != nullptr) {
        delete[] this->adjacency_matrix_;
    }
}

void EdgeWeightReader::fetchDimension() {
    std::string name;
    std::string dimension;
    std::string type;

    getline(this->file_stream_, name);
    getline(this->file_stream_, dimension);
    getline(this->file_stream_, type);

    std::smatch matches;

    if (std::regex_match(dimension, matches, dimension_regex_)) {
        this->dimension_ = std::stoi(matches[2]); 
    }
}

void EdgeWeightReader::prepare() {
    std::clog << "Preparing edge weight section" << std::endl;

    this->file_stream_ = std::ifstream(this->file_path_, std::ios::in);

    if (!this->file_stream_.is_open()) {
        throw std::runtime_error("could not open the desired file");
    }    
}
void EdgeWeightReader::process() {
    std::clog << "Processing: " << this->file_path_ << std::endl;
    
    this->fetchDimension();
    if (this->dimension_ == -1) throw std::runtime_error("invalid entry dimension");

    this->adjacency_matrix_ = new unsigned[this->dimension_ * this->dimension_];

    for (int i = 0; i < this->dimension_; i++) {
        for (int j = 0; j < this->dimension_; j++) {
            this->file_stream_ >> this->adjacency_matrix_[i * this->dimension_ + j];
        }
    }
}

unsigned* EdgeWeightReader::getAdjacencyMatrix() {
    return adjacency_matrix_;
}

int EdgeWeightReader::getAdjacencyMatrixSize() {
    return this->dimension_;
}
