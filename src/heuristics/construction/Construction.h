#ifndef HEURISTICS_CONSTRUCTION_CONSTRUCTION_H
#define HEURISTICS_CONSTRUCTION_CONSTRUCTION_H

#include <queue>

#include "../../graph-structs/adjacency-list/adjacency-list.h"

class Construction {
protected:
    unsigned* adjacency_matrix_;
    int matrix_size_;
    AdjacencyList* adjacency_list_;
public:
    Construction(unsigned* adjacency_matrix, const int& matrix_size, AdjacencyList* adjacency_list);
    virtual ~Construction();

    virtual int* getSolution(const unsigned& origin) = 0;
};

#endif // define HEURISTICS_CONSTRUCTION_CONSTRUCTION_H
