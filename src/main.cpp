#include <iostream>

#include "reader/reader-factory/reader-factory.h"
#include "heuristics/construction/greedy/greedy.h"
#include "heuristics/construction/nearest-insertion/nearest-insertion.h"
#include "heuristics/movement/two-opt/two-opt.h"
#include "heuristics/movement/swap/swap.h"
#include "heuristics/movement/vnd/vnd.h"
#include "grasp/grasp.h"

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
        // showMatrix(reader->getAdjacencyMatrix(), reader->getAdjacencyMatrixSize());
        // reader->getAdjacencyList()->show();
#endif
        // auto construction_heuristic = NearestInsertion(reader->getAdjacencyMatrix(), reader->getAdjacencyMatrixSize(), reader->getAdjacencyList());
        // // auto construction_heuristic = Greedy(reader->getAdjacencyMatrix(), reader->getAdjacencyMatrixSize(), reader->getAdjacencyList());
        // int* solution = construction_heuristic.getSolution(0);

        // const int construction_evaluation = evaluation(reader->getAdjacencyMatrix(), solution, reader->getAdjacencyMatrixSize());

        // std::clog << "Evaluation: " << construction_evaluation << std::endl;

        // std::clog << "Sequence: ";
        // for (int i = 0; i < reader->getAdjacencyMatrixSize(); i++)
        //     std::clog << solution[i] << " ";
        // std::clog << std::endl;

        // std::clog << "-----------------------------------------------------------------------------" << std::endl;

        // auto movement_heuristic = VND(reader->getAdjacencyMatrix(), reader->getAdjacencyMatrixSize());

        // // auto movement_heuristic = TwoOpt(reader->getAdjacencyMatrix(), reader->getAdjacencyMatrixSize());
        // // auto movement_heuristic = Swap(reader->getAdjacencyMatrix(), reader->getAdjacencyMatrixSize());
        // auto new_eval = movement_heuristic.getNewMovement(solution, construction_evaluation);
        // std::clog << "New Evaluation: " << new_eval << std::endl;

        // std::clog << "New Sequence: ";
        // for (int i = 0; i < reader->getAdjacencyMatrixSize(); i++)
        //     std::clog << solution[i] << " ";
        // std::clog << std::endl;

        // delete solution;


        int solution[reader->getAdjacencyMatrixSize()];
        Grasp grasp(reader->getAdjacencyMatrix(), reader->getAdjacencyMatrixSize(), reader->getAdjacencyList());
        std::clog << grasp.analyse(1, 0.5f, solution) << std::endl;

    } catch (const std::exception& e) {
        std::clog << "Failed - what(): " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
