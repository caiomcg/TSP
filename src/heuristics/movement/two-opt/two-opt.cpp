#include "two-opt.h"

#include <algorithm>
#include <iostream>
#include <cstring>

TwoOpt::TwoOpt(unsigned* adjacency_matrix, const unsigned& size) : Movement(adjacency_matrix, size) {}
TwoOpt::~TwoOpt() {}

int TwoOpt::partialEvaluation(int* solution, const int& i, const int& k, const unsigned& size) {
    int sum = 0;
    int inverter = 0;

    for (int c = 0; c < i - 1; c++) {
        sum += adjacency_matrix_[solution[c] * size + solution[c + 1]];
    }

    sum += adjacency_matrix_[solution[i - 1] * size + solution[k]];

    for (int c = k; c > i; c--) {
        sum += adjacency_matrix_[solution[c] * size + solution[c - 1]];
        inverter++;
    }


    sum += adjacency_matrix_[solution[i] * size + solution[k + 1]];

    for (unsigned j = k + 1; j < size - 1; j++) {
        sum += adjacency_matrix_[solution[j] * size + solution[j + 1]];
    }

    sum += adjacency_matrix_[solution[size - 1] * size + solution[0]];

    return sum;
}

int* TwoOpt::swap(int* solution, const int& i, const int& k, const unsigned& size) {
    int inverter = 0;

    std::clog << "PRE SWAP: ";
    for (int f = 0; f < this->size_; f++) {
        if (f == i || f == k) std::clog << " | "; 
        std::clog << solution[f] << " ";
    }
    std::clog << std::endl;
    
    for (int c = i; c <= k / 2; c++) {
        std::clog << c << " " << k - inverter << std::endl;
        std::swap(solution[k - inverter], solution[c]);
        inverter++;
    }

    std::clog << "POS SWAP: ";
    for (int f = 0; f < this->size_; f++) {
        if (f == i || f == k) std::clog << " | "; 
        std::clog << solution[f] << " ";
    }
    std::clog << std::endl;
    return solution;
}

int TwoOpt::getNewMovement(int* solution, int evaluation) {
    std::clog << "Performing TwoOpt" << std::endl;
    bool improved = true;

    // std::clog << "Pre TwoOpt: ";
    //     for (int i = 0; i < this->size_; i++)
    //         std::clog << solution[i] << " ";
    //     std::clog << std::endl;


    int best_i = -1;
    int best_j = -1;
    
    while (improved) {
        improved = false;
        for (unsigned i = 1; i < size_ - 2; i++) {
            for (unsigned j = i + 1; j < size_ - 1; j++) {
                // std::clog << "[" << solution[i] << "][" << solution[i - 1] << "] " << adjacency_matrix_[solution[i] * size_ + solution[(i - 1)]] <<  std::endl;
                // std::clog << "[" << solution[j] << "][" << solution[j + 1] << "] " << adjacency_matrix_[solution[j] * size_ + solution[(j + 1)]] << std::endl;
                // std::clog << "[" << solution[i] << "][" << solution[j + 1] << "] " << adjacency_matrix_[solution[i] * size_ + solution[(j + 1)]] << std::endl;
                // std::clog << "[" << solution[j] << "][" << solution[i - 1] << "] " << adjacency_matrix_[solution[j] * size_ + solution[(i - 1)]] << std::endl;
                
                // Compares if the two vertices that will be cut are better than the ones that 
                // will now be used. If the new one is better construct a new solution array
                // and check if the evaluation is better

                // TODO: DO NOT REALLOC FOR EVERY NEW SET
                if (adjacency_matrix_[solution[i] * size_ + solution[(i - 1)]] + adjacency_matrix_[solution[j] * size_ + solution[(j + 1)]] >= 
                    adjacency_matrix_[solution[i] * size_ + solution[(j + 1)]] + adjacency_matrix_[solution[j] * size_ + solution[(i - 1)]]) {                    
                    // int* new_solution = swap(solution, i, j, size_);

                    int new_evaluation = partialEvaluation(solution, i, j, size_);
           
                    if (new_evaluation < evaluation) {
                        best_i = i;
                        best_j = j;

                        evaluation = new_evaluation;
                        improved = true;
                    }
                }
            }
        }
        if (best_i >= 0 && best_j >= 0) {    
            this->swap(solution, best_i, best_j, size_);
            std::clog << "Post twoopt: ";
            for (int i = 0; i < this->size_; i++)
                std::clog << solution[i] << " ";
            std::clog << std::endl;

            best_i = best_j = -1;
        }
    }


    // std::clog << "New Sequence: ";
    // for (int k = 0; k < size_; k++)
    //     std::clog << solution[k] << " ";
    // std::clog << std::endl;

    return evaluation;
}
