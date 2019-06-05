#ifndef HEURISTICS_CONSTRUCTION_BEST_INSERTION_BEST_INSERTION_H
#define HEURISTICS_CONSTRUCTION_BEST_INSERTION_BEST_INSERTION_H

#include "../Construction.h"

#include <queue>

#include "../../../graph-structs/adjacency-list/adjacency-list.h"

class BestInsertion final : public Construction {
public:
    BestInsertion(unsigned* adjacency_matrix, const int& matrix_size, AdjacencyList* adjacency_list);
    ~BestInsertion();

    int* getSolution(const unsigned& origin) override;
};

#endif // define HEURISTICS_CONSTRUCTION_BEST_INSERTION_BEST_INSERTION_H
