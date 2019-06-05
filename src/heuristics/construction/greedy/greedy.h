#ifndef HEURISTICS_CONSTRUCTION_GREEDY_GREEDY_H
#define HEURISTICS_CONSTRUCTION_GREEDY_GREEDY_H

#include "../Construction.h"

#include <queue>

#include "../../../graph-structs/adjacency-list/adjacency-list.h"

typedef std::priority_queue<neighbour, std::vector<neighbour>, std::greater<neighbour> > PriorityQueue;

class Greedy final : public Construction {
private:
    PriorityQueue priority_queue_;
public:
    Greedy(unsigned* adjacency_matrix, const int& matrix_size, AdjacencyList* adjacency_list);
    ~Greedy();

    int* getSolution(const unsigned& origin) override;
};

#endif // define HEURISTICS_CONSTRUCTION_GREEDY_GREEDY_H
