#include "swap.h"

#include <iostream>
#include <algorithm>

Swap::Swap(unsigned* adjacency_matrix, const unsigned& size) : Movement(adjacency_matrix, size) {}
Swap::~Swap() {}

int Swap::getNewMovement(int* solution, int evaluation) {
    // std::clog << "Performing Swap" << std::endl;
    int new_evaluation = 0;
    bool improved = true;

    while (improved) {
        improved = false;

        for (unsigned i = 1; i < size_; i++) {
            for (unsigned j = 1; j < size_; j++) {
                if ( i == j )
                    continue;

                std::swap(solution[i], solution[j]);

                new_evaluation = this->evaluation(adjacency_matrix_, solution, size_);

                if (new_evaluation >= evaluation) {
                    std::swap(solution[i], solution[j]);
                } else {
                    improved = true;
                    evaluation = new_evaluation;
                }
            }
        }
    }

    return evaluation;
}
