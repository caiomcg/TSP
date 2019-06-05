#include "edge-weight-reader.h"

#include <iostream>

EdgeWeightReader::EdgeWeightReader(const std::string& file_path) : Reader(file_path) {}
EdgeWeightReader::~EdgeWeightReader() {}

void EdgeWeightReader::prepare() {
    std::clog << "Preparing edge weight section" << std::endl;

    this->file_stream_ = std::ifstream(this->file_path_, std::ios::in);

    if (!this->file_stream_.is_open()) {
        throw std::runtime_error("could not open the desired file");
    }    
}
void EdgeWeightReader::process() {
    std::clog << "Processing: " << this->file_path_ << std::endl;
    
    this->fetchDimension(this->file_stream_);
    if (this->dimension_ == -1) throw std::runtime_error("invalid entry dimension");

    std::clog << "allocate" << std::endl;

    if (!this->allocateAdjacencyMatrixWith(this->dimension_ * this->dimension_)) {
        throw std::runtime_error("could not allocate the memory space");
    }

    this->adjacency_list_ = new AdjacencyList{this->dimension_};

     std::clog << "allocated" << std::endl;

    for (int i = 0; i < this->dimension_; i++) {
        for (int j = 0; j < this->dimension_; j++) {
            this->file_stream_ >> this->adjacency_matrix_[i * this->dimension_ + j];

            if (this->adjacency_matrix_[i * this->dimension_ + j]) {
                this->adjacency_list_->addNeighbour(i, j, this->adjacency_matrix_[i * this->dimension_ + j]);
            }
        }
    }
}
