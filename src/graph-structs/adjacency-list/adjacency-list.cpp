#include "adjacency-list.h"

AdjacencyList::AdjacencyList(const unsigned& size) : root_size_(size), vertices_(0) {
    this->list_ = new std::vector<neighbour>[size];
}

void AdjacencyList::addNeighbour(const unsigned& origin, const unsigned& destination, const int& weight) {
    this->list_[origin].push_back({
        destination,
        weight
    });
    this->vertices_++;
}
bool AdjacencyList::isNeighbour(const unsigned& origin, const unsigned& destination) {
    for (auto& element : this->list_[origin]) {
        if (element.vertice == destination) {
            return true;
        }
    }
    return false;
}

#include <iostream>

void AdjacencyList::show() const {
     for (unsigned i = 0; i < this->root_size_; i++) {
        for (unsigned j = 0; j < this->list_[i].size(); j++) {
            std::cout << this->list_[i][j].weight << "\t";
        }
        std::cout << std::endl;
    }
}

neighbour AdjacencyList::getNeighbour(const unsigned& origin, const unsigned& destination) {
    return this->list_[origin][destination];
}

unsigned AdjacencyList::getNeighbourSize(const unsigned& origin) {
    return this->list_[origin].size();
}

unsigned AdjacencyList::getVertices() const {
    return this->vertices_;
}
