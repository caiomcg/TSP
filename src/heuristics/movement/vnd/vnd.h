#ifndef HEURISTICS_MOVEMENT_VND_H
#define HEURISTICS_MOVEMENT_VND_H

#include "../movement.h"

class VND final : public Movement {
public:
    VND(unsigned* adjacency_matrix, const unsigned& size);
    ~VND();

    int getNewMovement(int* solution, int evaluation) override;
};

#endif // define HEURISTICS_MOVEMENT_VND_H
