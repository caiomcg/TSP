#include "greedy.h"

Greedy::Greedy(unsigned* adjacency_matrix, const int& matrix_size, AdjacencyList* adjacency_list)
    : Construction(adjacency_matrix, matrix_size, adjacency_list) {}

Greedy::~Greedy() {}

#include <iostream>

int* Greedy::getSolution(const unsigned& origin) {
    std::vector<int> C(matrix_size_);

    for (unsigned i = 0; i < C.size(); i++) {
        C[i] = i;
    }
    
    bool* processed = new bool[matrix_size_]();
    int* solution = new int[matrix_size_]();
    
    int current_vertex = -1;
    unsigned count = 0;

    priority_queue_.push({ origin, 0 }); // Start from the origin, which costs 0;

    // std::clog << "Size: " << matrix_size_ << std::endl;
    // std::clog << "Processed: " << processed[0] << std::endl;
    // std::clog << "solution: " << solution[0] << std::endl;

    while (true) {
        current_vertex = -1;
        while (!priority_queue_.empty()) {
            int vertex = priority_queue_.top().vertice;
            priority_queue_.pop();

            if (!processed[vertex]) {
                processed[vertex] = true;
                current_vertex = vertex;
                solution[count++] = vertex;

                for (unsigned i = 0; i < C.size(); i++) {
                    if (C[i] == current_vertex) C.erase(C.begin() + i);
                }
                    
                while(!priority_queue_.empty()) priority_queue_.pop();
                break;
            }
        }

        if (current_vertex == -1) break;

        for (unsigned i = 0; i < C.size(); i++) {
        //     std::clog << current_vertex << " " << C[i] << std::endl;
        //     std::clog << "Will add: {" << C[i] << ", " << adjacency_list_->getWeight(current_vertex, C[i]) << " }" << std::endl;
            priority_queue_.push({ C[i], adjacency_list_->getWeight(current_vertex, C[i]) });
        }
    }

    return solution;
}
