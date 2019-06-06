#ifndef HEURISTICS_CONSTRUCTION_BEST_INSERTION_BEST_INSERTION_H
#define HEURISTICS_CONSTRUCTION_BEST_INSERTION_BEST_INSERTION_H

#include "../Construction.h"

#include <queue>

#include "../../../graph-structs/adjacency-list/adjacency-list.h"

class NearestInsertion final : public Construction {
public:
    NearestInsertion(unsigned* adjacency_matrix, const int& matrix_size, AdjacencyList* adjacency_list);
    ~NearestInsertion();

    int* getSolution(const unsigned& origin) override;
};

#endif // define HEURISTICS_CONSTRUCTION_BEST_INSERTION_BEST_INSERTION_H
