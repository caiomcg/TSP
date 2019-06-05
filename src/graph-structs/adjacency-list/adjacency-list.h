#ifndef GRAPH_STRUCTS_ADJACENCY_LIST_ADJACENCY_LIST_H
#define GRAPH_STRUCTS_ADJACENCY_LIST_ADJACENCY_LIST_H

#include <vector>

typedef struct {
    unsigned vertice;
    int weight;
} t_neighbour;

class AdjacencyList final {
private:
    std::vector<t_neighbour>* list_;
    unsigned root_size_;
    unsigned vertices_;
public:
    AdjacencyList(const unsigned& size);

    void addNeighbour(const unsigned& origin, const unsigned& destination, const int& weight);
    bool isNeighbour(const unsigned& origin, const unsigned& destination);

    void show() const;

    unsigned getVertices() const;
};

#endif // define GRAPH_STRUCTS_ADJACENCY_LIST_ADJACENCY_LIST_H
