#include "display-data-reader.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

DisplayDataReader::DisplayDataReader(const std::string& file_path) : Reader(file_path) {}
DisplayDataReader::~DisplayDataReader() {}

unsigned DisplayDataReader::distanceBetweenNodes(const std::pair<double, double>& begin, const std::pair<double, double>& end) {

    // std::clog << "sqrt(pow((" << end.first << "-" << begin.first <<"), 2) + pow((" <<end.second << "-" << begin.second << "), 2))" << std::endl;
    // std::clog << "sqrt(pow(" <<end.first - begin.first << "), 2) + pow((" << end.second - begin.second << "), 2))" << std::endl;
    // std::clog << "sqrt(" << pow((end.first - begin.first), 2) << " + " << pow((end.second - begin.second), 2) << ")" << std::endl;
    // std::clog << "sqrt(" << pow((end.first - begin.first), 2) + pow((end.second - begin.second), 2) << ")" << std::endl;
    // std::clog << sqrt(pow((end.first - begin.first), 2) + pow((end.second - begin.second), 2)) << std::endl;
    return sqrt(pow((end.first - begin.first), 2) + pow((end.second - begin.second), 2));
}

void DisplayDataReader::prepare() {
    std::clog << "Preparing display data section" << std::endl;
    this->file_stream_ = std::ifstream(this->file_path_, std::ios::in);

    if (!this->file_stream_.is_open()) {
        throw std::runtime_error("could not open the desired file");
    }    
}

void DisplayDataReader::process() {
    std::clog << "Processing " << this->file_path_ << std::endl;
    
    std::regex line_regex(R"(\d+(\ )+(\d+\.\d+)(\ )+(\d+\.\d+))");

    this->fetchDimension(this->file_stream_);
    if (this->dimension_ == -1) throw std::runtime_error("invalid entry dimension");

    if (!this->allocateAdjacencyMatrixWith(this->dimension_ * this->dimension_)) {
        throw std::runtime_error("could not allocate the memory space");
    }

    std::string line;
    std::smatch matches;
    std::vector<std::pair<double, double>> points;

    while (getline(this->file_stream_, line)) {
        int index = 0;
        std::pair<double, double> point(0,0);

        std::stringstream ss(line);
        ss >> index >> point.first >> point.second;

        points.push_back(point);
    }

    for (int i = 0; i < this->dimension_; i++) {
        for (int j = i + 1; j < this->dimension_; j++) {
            this->adjacency_matrix_[i * this->dimension_ + j] = this->adjacency_matrix_[j * this->dimension_ + i] = this->distanceBetweenNodes(
                points[i],
                points[j]
            );
        }
    }
}
