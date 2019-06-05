#include <iostream>

#include "reader/reader-factory/reader-factory.h"
#include "heuristics/construction/greedy/greedy.h"
#include "heuristics/construction/best-insertion/best-insertion.h"

void showMatrix(const unsigned* matrix, const int& dimension) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            std::clog << matrix[i * dimension + j] << " ";
        }
        std::clog << "\n";
    }
}

int evaluation(const unsigned* adjacency_matrix, const int *solution, const int& size ) {
    int sum = 0;

    for (int i = 0; i < size - 1; ++i) {
        sum += adjacency_matrix[solution[i] * size + solution[i + 1]];
    }
    sum += adjacency_matrix[solution[0] * size + solution[size - 1]];

    return sum;
}

int main(int argc, char** argv) {
    (void) argc; // unused parameter

    try {
        auto reader = ReaderFactory().createReader(argv[1]);
        
        reader->prepare();
        reader->process();

#ifdef DEBUG
        showMatrix(reader->getAdjacencyMatrix(), reader->getAdjacencyMatrixSize());
        reader->getAdjacencyList()->show();
#endif
    
        auto construction_heuristic = BestInsertion(reader->getAdjacencyMatrix(), reader->getAdjacencyMatrixSize(), reader->getAdjacencyList());
        int* solution = construction_heuristic.getSolution(0);

        std::clog << "Evaluation: " << evaluation(reader->getAdjacencyMatrix(), solution, reader->getAdjacencyMatrixSize()) << std::endl;

        for (int i = 0; i < reader->getAdjacencyMatrixSize(); i++)
            std::clog << solution[i] << " ";
        std::clog << std::endl;


        delete[] solution;
    } catch (const std::exception& e) {
        std::clog << "Failed - what(): " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
