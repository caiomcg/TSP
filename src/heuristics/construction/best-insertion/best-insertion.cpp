#include "best-insertion.h"

#include <limits>

BestInsertion::BestInsertion(unsigned* adjacency_matrix, const int& matrix_size, AdjacencyList* adjacency_list)
    : Construction(adjacency_matrix, matrix_size, adjacency_list) {}

BestInsertion::~BestInsertion() {}

#include <iostream>

int* BestInsertion::getSolution(const unsigned& origin) {
    int* solution = new int[matrix_size_]();
    bool* processed = new bool[matrix_size_]();

    solution[0]  = origin;
    processed[0] = true;

    int min_vertice_weight = std::numeric_limits<int>::max();
    int vertice = -1;
    int count = 1;

    for (unsigned i = 0; i < adjacency_list_->getNeighbourSize(0); i++) {
        auto neighbour = adjacency_list_->getNeighbour(0, i + 1);
        if (!processed[neighbour.vertice] && neighbour.weight < min_vertice_weight) {
            min_vertice_weight = neighbour.weight;
            vertice = neighbour.vertice;
        }
    }

    processed[vertice] = true;
    solution[count++] = vertice;

    int matrix[2][matrix_size_];

    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < matrix_size_; i++) {
            matrix[j][i] = std::numeric_limits<int>::max();
        }
    }

    for (int j = 0; j < 2; j++) {
        for (unsigned i = 0; i < adjacency_list_->getNeighbourSize(0); i++) {
            matrix[j][adjacency_list_->getNeighbour(j, i + 1).vertice] = adjacency_list_->getNeighbour(j, i + 1).weight;
        }
    }

    min_vertice_weight = std::numeric_limits<int>::max();
    for (int i = 0; i < matrix_size_; i++) {
        int second = matrix[0][i] + matrix[1][i];
        if ( !processed[i] and second < min_vertice_weight )
            min_vertice_weight = second,
            vertice = i;
    }

    processed[vertice] = 1;
    solution[count++] = vertice;

    for (int i = count; i < matrix_size_; i++) {
        int a, b;
        vertice = -1;
        min_vertice_weight = std::numeric_limits<int>::max();
        for (int j = 1; j < matrix_size_; j++) {

            if ( !processed[j] ) {
                int dist[count];
                for (int k = 0; k < count; ++k) {
                    dist[k] = adjacency_matrix_[solution[k] * matrix_size_ + j];
                }

                for (int k = 0; k < count - 1; ++k) {
                    if (dist[k] + dist[k + 1] < min_vertice_weight) {
                        a = k;
                        b = k + 1;
                        vertice = j;
                        min_vertice_weight = dist[k] + dist[k + 1];
                    }
                }

                if (dist[count - 1] + dist[0] < min_vertice_weight) {
                    a = count - 1; 
                    b = 0;
                    vertice = j;
                    min_vertice_weight = dist[0] + dist[a];
                }
            }
        }

        processed[vertice] = true;

        if ( b != 0) {
            for (int j = count; j >= b; j--){
                solution[j + 1] = solution[j];
            }

            solution[b] = vertice;
            count++;
        } else {
            solution[count++] = vertice;
        }
    }

    delete[] processed;
    return solution;
}
