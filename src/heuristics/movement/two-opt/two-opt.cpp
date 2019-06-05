#include "two-opt.h"

#include <algorithm>
#include <iostream>
#include <cstring>

TwoOpt::TwoOpt(unsigned* adjacency_matrix, const unsigned& size) : Movement(adjacency_matrix, size) {}
TwoOpt::~TwoOpt() {}


int* TwoOpt::swap(int* solution, const int& i, const int& k, const unsigned& size) {
    int* new_solution = new int[size]();

    for (int c = 0; c <= i - 1; c++) {
        new_solution[c] = solution[c];
    }

    int inverter = 0;
    for (int c = i; c <= k; c++) {
        new_solution[c] = solution[k - inverter];
        inverter++;
    }

    for (int j = k + 1; j < size; j++) {
        new_solution[j] = solution[j];
    }

    return new_solution;
}

int TwoOpt::getNewMovement(int* solution, int evaluation) {
    bool improved = true;

    while (improved) {
        improved = false;
        for (int i = 1; i < size_ - 2; i++) {
            for (int j = i + 1; j < size_ - 1; j++) {
                if (adjacency_matrix_[i * size_ + (i - 1)] + adjacency_matrix_[(j + 1) * size_ + j] >= 
                    adjacency_matrix_[i * size_ + (j + 1)] + adjacency_matrix_[(i - 1) * size_ + j]) {
                    
                    int* new_solution = swap(solution, i, j, size_);

                    int new_evaluation = this->evaluation(adjacency_matrix_, new_solution, size_);
           
                    if (new_evaluation < evaluation) {
                        delete[] solution;
                        solution = new_solution;
                        new_solution = nullptr;

                        evaluation = new_evaluation;
                        improved = true;
                    }
                }
            }
        }
    }

    return evaluation;
}
