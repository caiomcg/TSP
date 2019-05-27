#include "reader.h"

Reader::Reader(const std::string file_path) : file_path_{file_path}, 
    dimension_regex_{R"((DIMENSION):\ (\d+))"}, name_regex_{R"((NAME): (.+))"},
    adjacency_matrix_{nullptr}, dimension_{-1} {}

Reader::~Reader() {
    if (this->adjacency_matrix_ != nullptr) {
        delete[] this->adjacency_matrix_;
    }
}

bool Reader::allocateAdjacencyMatrixWith(const unsigned& size) {
    if (this->adjacency_matrix_ == nullptr) {
        this->adjacency_matrix_ = new unsigned[size];
        return true;
    }
    return false;
}

void Reader::fetchDimension(std::ifstream& file_stream) {
    std::string name;
    std::string dimension;
    std::string type;

    getline(file_stream, name);
    getline(file_stream, dimension);
    getline(file_stream, type);

    std::smatch matches;

    if (std::regex_match(dimension, matches, dimension_regex_)) {
        this->dimension_ = std::stoi(matches[2]); 
    }
}

unsigned* Reader::getAdjacencyMatrix() {
    return this->adjacency_matrix_;
}

int Reader::getAdjacencyMatrixSize() {
    return this->dimension_;
}
