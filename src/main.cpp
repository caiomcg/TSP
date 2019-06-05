#include <iostream>

#include "reader/reader-factory/reader-factory.h"

void showMatrix(const unsigned* matrix, const int& dimension) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            std::clog << matrix[i * dimension + j] << " ";
        }
        std::clog << "\n";
    }
}

int main(int argc, char** argv) {
    (void) argc; // unused parameter

    try {
        auto reader = ReaderFactory().createReader(argv[1]);
        
        reader->prepare();
        reader->process();

        // showMatrix(reader->getAdjacencyMatrix(), reader->getAdjacencyMatrixSize());
        reader->getAdjacencyList()->show();

    } catch (const std::exception& e) {
        std::clog << "Failed - what(): " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
