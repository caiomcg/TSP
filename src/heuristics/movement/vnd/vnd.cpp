#include "vnd.h"

#include "../two-opt/two-opt.h"
#include "../swap/swap.h"

#include <iostream>

VND::VND(unsigned* adjacency_matrix, const unsigned& size) : Movement(adjacency_matrix, size) {}
VND::~VND() {}

int VND::getNewMovement(int* solution, int evaluation) {
    std::clog << "Performing VND" << std::endl;

    Movement* movements[2] = {new Swap(adjacency_matrix_, size_), new TwoOpt(adjacency_matrix_, size_)};
    unsigned count = 0;

    int new_evaluation = 0;

    while (count < 2) {
        std::clog << "VND will use: ";
        for (int i = 0; i < this->size_; i++)
            std::clog << solution[i] << " ";
        std::clog << std::endl;
        new_evaluation = movements[count]->getNewMovement(solution, evaluation);

        if (new_evaluation < evaluation) {
            // std::clog << "New Sequence: ";
            // for (unsigned i = 0; i < size_; i++)
            //     std::clog << solution[i] << " ";
            // std::clog << std::endl;
            evaluation = new_evaluation,
            count = 0;
        } else {
            count++;
        }
    }

    delete movements[0];
    delete movements[1];

    return evaluation;
}
