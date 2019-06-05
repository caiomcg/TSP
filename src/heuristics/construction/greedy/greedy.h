#ifndef HEURISTICS_CONSTRUCTION_GREEDY_GREEDY_H
#define HEURISTICS_CONSTRUCTION_GREEDY_GREEDY_H

#include "../Construction.h"

#include <queue>

#include "../../../graph-structs/adjacency-list/adjacency-list.h"

typedef std::priority_queue<neighbour, std::vector<neighbour>, std::greater<neighbour> > MIN_HEAP;

class Greedy final : public Construction {
private:
    MIN_HEAP min_heap;
public:
    Greedy(unsigned* adjacency_matrix, const int& matrix_size, AdjacencyList* adjacency_list);
    ~Greedy();

    int* getSolution(const unsigned& origin) override;
};

#endif // define HEURISTICS_CONSTRUCTION_GREEDY_GREEDY_H
