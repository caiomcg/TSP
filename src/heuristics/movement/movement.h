#ifndef HEURISTICS_MOVEMENT_MOVEMENT_H
#define HEURISTICS_MOVEMENT_MOVEMENT_H

class Movement {
protected:
    unsigned* adjacency_matrix_;
    unsigned size_;
    int evaluation(const unsigned* adjacency_matrix, const int *solution, const int& size);
public:
    Movement(unsigned* adjacency_matrix, const unsigned& size);
    virtual ~Movement();

    virtual int getNewMovement(int* solution, int evaluation) = 0;
};

#endif // define HEURISTICS_MOVEMENT_MOVEMENT_H
