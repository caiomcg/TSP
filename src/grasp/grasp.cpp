#include "grasp.h"

#include <random>
#include <ctime>

#include <limits>
#include <vector>
#include <algorithm>

#include <iostream>

Grasp::Grasp(unsigned* adjacency_matrix, const int& matrix_size, AdjacencyList* adjacency_list) 
    : adjacency_matrix_(adjacency_matrix), matrix_size_(matrix_size), adjacency_list_(adjacency_list), 
    vnd_(adjacency_matrix, matrix_size) {}


// Alpha of 0 is pure greedy, of 1 is randomized
void Grasp::construction(const int& origin, int *solution, const float& alpha) {
    bool* visited = new bool[matrix_size_](); // Visited candidate list
    int current_vertex = -1; // current selected vertex
    int count = 0; // Position to insert the vertex

    std::vector< int > candidates(matrix_size_); // candidate list
    std::vector<neighbour> restricted_candidate_list; // Restricted candidate list

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator

    for (int i = 0; i < matrix_size_; i++) { 
        solution[i] = 0; // Initialize solutions zeroed
        candidates[i] = i; // Initialize all the candidates (0, n-1)
    }

    // Start from the origin
    restricted_candidate_list.push_back({ (unsigned)origin, 0 });

    do { // While you have candidates, execute the procedure
        current_vertex = -1;
        while (!restricted_candidate_list.empty()) { // While we haven't picked an element
            int gt_min = 0; // Start range
            int gt_max = restricted_candidate_list.size() - 1; // End range
            int LCR = gt_min + alpha * ( gt_max - gt_min );  // Define the range 
            
            std::uniform_int_distribution<> distr(gt_min, LCR); // define the range to the randomizer
            
            int id = distr(eng); // Fetch a random number
            int selected_candidate = restricted_candidate_list[id].vertice; // This candidate will be added to the solution

            // std::clog << "gt_min: " << gt_min << std::endl; 
            // std::clog << "gt_max: " << gt_max << std::endl;
            // std::clog << "LCR: " << LCR << std::endl;
            // std::clog << "id: " << id << std::endl;
            // std::clog << "selected_candidate: " << selected_candidate << std::endl;

            if (!visited[selected_candidate]) { // If not visited
                visited[selected_candidate] = true; // Mark as visited
                current_vertex = selected_candidate; // Set as currently selected
                solution[count++] = selected_candidate; // Add the vertex to the solution
                
                for (unsigned i = 0; i < candidates.size(); i++) { // Remove the element from the candidate list
                    if (candidates[i] == current_vertex) {
                        candidates.erase(candidates.begin() + i);
                        break;
                    }
                }
                    
                restricted_candidate_list.clear(); // Clear the restricted candidate list
                break;
            }
        }

        for (unsigned i = 0; i < candidates.size(); i++) { // Iterate throug all possible candidates, now with one removed
            // Add the candidate and the weight from the one that was removed to the new possibility
            restricted_candidate_list.push_back({ (unsigned)candidates[i], adjacency_list_->getNeighbour(current_vertex, candidates[i]).weight });
        }
        // Order by the smallest weight, interesting for the greedier solution
        std::sort(restricted_candidate_list.begin(), restricted_candidate_list.end());
    } while(candidates.size());

    delete[] visited;
}


int Grasp::analyse(const int& iterations, const float& alpha, int* solution) {
    int evaluation = std::numeric_limits<int>::max();;

    for (int i = 0; i < iterations; i++) {

        this->construction(0, solution, alpha);

        // std::clog << "Constructed: ";
        // for (int i = 0; i < matrix_size_; i++)
        //     std::clog << solution[i] << "(" << i << ") ";
        // std::clog << std::endl;

        this->vnd_.getNewMovement( solution, this->evaluation( adjacency_matrix_, solution, matrix_size_));
        int temp_evaluation = this->evaluation( adjacency_matrix_, solution, matrix_size_);
        
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
