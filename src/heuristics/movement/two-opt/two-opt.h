#ifndef HEURISTICS_MOVEMENT_TWO_OPT_H
#define HEURISTICS_MOVEMENT_TWO_OPT_H

#include "../movement.h"

class TwoOpt final : public Movement {
protected:
    int* swap(int* solution, const int& i, const int& k, const unsigned& size);
public:
    TwoOpt(unsigned* adjacency_matrix, const unsigned& size);
    ~TwoOpt();

    int getNewMovement(int* solution, int evaluation) override;
};

#endif // define HEURISTICS_MOVEMENT_TWO_OPT_H
