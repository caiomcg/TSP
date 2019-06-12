#include "grasp.h"

#include <cstdlib>
#include <ctime>

#include <limits>
#include <vector>
#include <algorithm>

Grasp::Grasp(unsigned* adjacency_matrix, const int& matrix_size, AdjacencyList* adjacency_list) 
    : adjacency_matrix_(adjacency_matrix), matrix_size_(matrix_size), adjacency_list_(adjacency_list), 
    vnd_(adjacency_matrix, matrix_size) {}


int Grasp::construction(const int& origin, int *solution, const float& alpha) {
    int processed[matrix_size_], actual, count = 0;
    std::vector< int > C( matrix_size_ );
    std::vector< std::pair < int, int > > V( matrix_size_ );

    for ( int i = 0; i < matrix_size_; i++ ) {
        solution[i] = 0;
        processed[i] = 0;
        C[i] = i;
    }

    V.push_back(std::make_pair(0, origin));

    while (true) {
        actual = -1;
        while (!V.empty()) {
            srand( (unsigned)time(NULL) );
            int gt_min = 0;
            int gt_max = V.size() - 1;
            int LCR = gt_min + alpha * ( gt_max - gt_min );
            int id = rand() % (LCR + 1);
            int temp = V[id].second;

            if (!processed[temp]) {
                processed[temp] = 1;
                actual = temp;
                solution[count++] = temp;
                
                for (int i = 0; i < C.size(); i++) {
                    if (C[i] == actual) {
                        C.erase(C.begin() + i);
                        break;
                    }
                }
                    
                V.clear();
                break;
            }
        }

        if (actual == -1) break;

        for (int i = 0; i < C.size(); i++) {
            V.push_back(std::make_pair(adjacency_list_->getNeighbour(actual,C[i]).weight, C[i]));
        }
        std::sort(V.begin(), V.end());
    }
}


int Grasp::analyse(const int& iterations, const float& alpha, int* solution) {
    int evaluation = std::numeric_limits<int>::max();;

    for (int i = 0; i < iterations; i++) {
        int new_solution[matrix_size_];

        this->construction(0.5f, new_solution, alpha);
        this->vnd_.getNewMovement( new_solution, this->evaluation( adjacency_matrix_, new_solution, matrix_size_));
        int temp_evaluation = this->evaluation( adjacency_matrix_, new_solution, matrix_size_);
        
        if (temp_evaluation < evaluation) {
            evaluation = temp_evaluation;
        }

    }
    return evaluation;
}

int Grasp::evaluation(const unsigned* adjacency_matrix, const int *solution, const int& size ) {
    int sum = 0;
    
    for (int i = 0; i < size - 1; ++i) {
        sum += adjacency_matrix[solution[i] * size + solution[i + 1]];
    }
    sum += adjacency_matrix[solution[0] * size + solution[size - 1]];


    return sum;
}
