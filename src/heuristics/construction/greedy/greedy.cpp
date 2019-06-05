#include "greedy.h"

Greedy::Greedy(unsigned* adjacency_matrix, const int& matrix_size, AdjacencyList* adjacency_list)
    : Construction(adjacency_matrix, matrix_size, adjacency_list) {}

Greedy::~Greedy() {}

#include <iostream>

int* Greedy::getSolution(const unsigned& origin) {
    int* solution   = new int [matrix_size_]();
    bool* visited = new bool[matrix_size_]();
    
    std::vector<int> nodes(matrix_size_);

    unsigned solution_pos = 0;

    for (unsigned i = 0; i < nodes.size(); i++) {
        nodes[i] = i;
    }

    min_heap.push({ origin, 0 }); // Start from the origin, which costs 0;

    do {
        int current_vertex = -1;
        
        // If we have an element on the min heap
        while (!min_heap.empty()) {
            int vertex = min_heap.top().vertice; // Get the vertice where the smallest element represents
            min_heap.pop(); // Remove the smallest

            if (!visited[vertex]) { // If we have not visited
                
                // Set as visited and add the vertice as the next part of the solution
                visited[vertex] = true;
                current_vertex = vertex;
                solution[solution_pos++] = vertex;

                // Remove the element from the nodes list
                for (unsigned i = 0; i < nodes.size(); i++) {
                    if (nodes[i] == current_vertex) nodes.erase(nodes.begin() + i);
                }
                    
                // Remove all elements from the queue as we will look only in the level of the current_vertex
                while(!min_heap.empty()) min_heap.pop();
                break;
            }
        }

        // Copy all connections between the current_vertex and the other nodes
        for (unsigned i = 0; i < nodes.size(); i++) {
            min_heap.push({ (unsigned)nodes[i], adjacency_list_->getNeighbour(current_vertex, nodes[i] - 1).weight });
        }
    } while (nodes.size());

    delete[] visited;
    return solution;
}
