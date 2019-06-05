#ifndef GRAPH_STRUCTS_ADJACENCY_LIST_ADJACENCY_LIST_H
#define GRAPH_STRUCTS_ADJACENCY_LIST_ADJACENCY_LIST_H

#include <vector>

struct neighbour {
    unsigned vertice;
    int weight;

    inline bool operator > (const neighbour& rhs) {
        return this->weight > rhs.weight; 
    }
};

inline bool operator >(const neighbour &lhs, const neighbour &rhs)
{
    return lhs.weight > rhs.weight; 
}

inline bool operator <(const neighbour &lhs, const neighbour &rhs)
{
    return lhs.weight < rhs.weight; 
}

class AdjacencyList final {
private:
    std::vector<neighbour>* list_;
    unsigned root_size_;
    unsigned vertices_;
public:
    AdjacencyList(const unsigned& size);

    void addNeighbour(const unsigned& origin, const unsigned& destination, const int& weight);
    bool isNeighbour(const unsigned& origin, const unsigned& destination);

    void show() const;

    int getWeight(const unsigned& origin, const unsigned& destination);
    unsigned getVertices() const;
};

#endif // define GRAPH_STRUCTS_ADJACENCY_LIST_ADJACENCY_LIST_H
