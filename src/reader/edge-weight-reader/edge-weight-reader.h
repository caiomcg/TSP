#ifndef READER_EDGE_WEIGHT_READER_H
#define READER_EDGE_WEIGHT_READER_H

#include <fstream>

#include "../reader-interface/reader.h"

class EdgeWeightReader final : public Reader {
private:
    std::ifstream file_stream_;
    unsigned* adjacency_matrix_;
    int dimension_;

    void fetchDimension();
public:
    EdgeWeightReader(const std::string& file_path);
    ~EdgeWeightReader();

    void prepare() noexcept(false) override;
    void process() override;
    unsigned* getAdjacencyMatrix() override;
    int getAdjacencyMatrixSize() override;
};

#endif // define READER_EDGE_WEIGHT_READER_H
