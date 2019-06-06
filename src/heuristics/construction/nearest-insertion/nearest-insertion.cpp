#include "nearest-insertion.h"

#include <limits>
#include <algorithm>

NearestInsertion::NearestInsertion(unsigned* adjacency_matrix, const int& matrix_size, AdjacencyList* adjacency_list)
    : Construction(adjacency_matrix, matrix_size, adjacency_list) {}

NearestInsertion::~NearestInsertion() {}

#include <iostream>

int* NearestInsertion::getSolution(const unsigned& origin) {
    int* solution = new int[matrix_size_]();
    bool* processed = new bool[matrix_size_]();

    int min_vertice_weight = std::numeric_limits<int>::max();
    int min_vertice = -1;
    int count = 1;

    // nearest insertion heuristic
    // Step 1. Start with a sub-graph consisting of node i only.
    // Step 2. Find node r such that cir is minimal and form sub-tour i-r-i.
    // Step 3. (Selection step) Given a sub-tour, find node r not in the sub-tour closest to any node j in the sub-tour; i.e. with minimal crj
    // Step 4. (Insertion step) Find the arc (i, j) in the sub-tour which minimizes cir + crj - cij . Insert r between i and j.
    // Step 5. If all the nodes are added to the tour, stop. Else go to step 3

    // Step 1: Start by adding the node 'i' to the solution
    solution[0]  = origin;
    processed[0] = true;

    // Step 2:
    // Find the node 'r' with the minimum distance between i and r
    for (unsigned i = 0; i < adjacency_list_->getNeighbourSize(origin); i++) {
        auto neighbour = adjacency_list_->getNeighbour(origin, i);

        // Not processed and has a smaller weight, pick this node as r
        if (!processed[neighbour.vertice] && neighbour.weight < min_vertice_weight) {
            min_vertice_weight = neighbour.weight;
            min_vertice = neighbour.vertice;
        }
    }

    // Add r to the second position of the solution forming a cycle
    processed[min_vertice] = true;
    solution[count++] = min_vertice;

    for (int i = count; i < matrix_size_; i++) {
        int insert_position = 0;
        
        min_vertice = -1;
        min_vertice_weight = std::numeric_limits<int>::max();
        
        // Step 3:
        // Look for the minimum to insert in between
        for (int j = 1; j < matrix_size_; j++) { // Discarding the origin look at all the nodes

            if (!processed[j]) { // If it is not on the solution
                int dist[count];

                // Get the distance between the found node and all the node in the cycle
                for (int k = 0; k < count; k++) {
                    dist[k] = adjacency_matrix_[solution[k] * matrix_size_ + j];
                }

                // Iterate through the cycle looking for the smallest edge
                for (int k = 0; k < count - 1; k++) {
                    if (dist[k] + dist[k + 1] < min_vertice_weight) {
                        insert_position = k + 1;
                        min_vertice = j;
                        min_vertice_weight = dist[k] + dist[k + 1];
                    }
                }
                
                // Check if it should fit between the end of the cycle, parte that connects end to origin
                if (dist[count - 1] + dist[0] < min_vertice_weight) {
                    insert_position = count;
                    min_vertice = j;
                    min_vertice_weight = dist[0] + dist[count - 1];
                }
            }
        }

        // Mark the minimum vertice as processed
        processed[min_vertice] = true;

        // Shift the elements
        for (int j = count; j >= insert_position && insert_position != 0; j--) {
            solution[j + 1] = solution[j];
        }

        // Add the vertice to the solution list
        solution[insert_position] = min_vertice;
        count++;
    }

    delete[] processed;
    return solution;
}
