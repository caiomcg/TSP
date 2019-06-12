#ifndef GRASP_GRASP_H
#define GRASP_GRASP_H

#include "../graph-structs/adjacency-list/adjacency-list.h"
#include "../heuristics/movement/vnd/vnd.h"

class Grasp {
private:
    unsigned* adjacency_matrix_;
    int matrix_size_;
    AdjacencyList* adjacency_list_;
    VND vnd_;

    int evaluation(const unsigned* adjacency_matrix, const int *solution, const int& size);
public:
    Grasp(unsigned* adjacency_matrix, const int& matrix_size, AdjacencyList* adjacency_list);
    
    void construction(const int& origin, int *solution, const float& alpha);
    int analyse(const int& iterations, const float& alpha, int* solution);
};

#endif // define GRASP_GRASP_H
