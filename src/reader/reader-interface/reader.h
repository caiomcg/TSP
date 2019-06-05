#ifndef READER_READER_INTERFACE_READER_H
#define READER_READER_INTERFACE_READER_H

#include <string>
#include <fstream>
#include <regex>

#include "../../graph-structs/adjacency-list/adjacency-list.h"

class Reader {
protected:
    std::string file_path_;
    std::regex  dimension_regex_;
    std::regex  name_regex_;

    unsigned* adjacency_matrix_;
    AdjacencyList* adjacency_list_;
    
    int dimension_;

    bool allocateAdjacencyMatrixWith(const unsigned& size);
    void fetchDimension(std::ifstream& file_stream);
public:
    Reader(const std::string file_path);
    virtual ~Reader();
    
    unsigned* getAdjacencyMatrix();
    int getAdjacencyMatrixSize();

    AdjacencyList* getAdjacencyList();

    virtual void prepare() noexcept(false) = 0;
    virtual void process() = 0;
};

#endif // define READER_READER_H
