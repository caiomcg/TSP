#include "Construction.h"

Construction::Construction(unsigned* adjacency_matrix, const int& matrix_size, AdjacencyList* adjacency_list) 
    : adjacency_matrix_(adjacency_matrix), matrix_size_(matrix_size), adjacency_list_(adjacency_list) {}
Construction::~Construction() {}
