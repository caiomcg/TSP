#ifndef HEURISTICS_MOVEMENT_SWAP_H
#define HEURISTICS_MOVEMENT_SWAP_H

#include "../movement.h"

class Swap final : public Movement {
public:
    Swap(unsigned* adjacency_matrix, const unsigned& size);
    ~Swap();

    int getNewMovement(int* solution, int evaluation) override;
};

#endif // define HEURISTICS_MOVEMENT_SWAP_H
