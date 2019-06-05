#include "movement.h"

#include <iostream>

Movement::Movement(unsigned* adjacency_matrix,  const unsigned& size) : adjacency_matrix_(adjacency_matrix), size_(size) {}
Movement::~Movement() {}

int Movement::evaluation(const unsigned* adjacency_matrix, const int *solution, const int& size ) {
    int sum = 0;
    
    for (int i = 0; i < size - 1; ++i) {
        sum += adjacency_matrix[solution[i] * size + solution[i + 1]];
    }
    sum += adjacency_matrix[solution[0] * size + solution[size - 1]];


    return sum;
}
