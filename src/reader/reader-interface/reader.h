#ifndef READER_READER_INTERFACE_READER_H
#define READER_READER_INTERFACE_READER_H

#include <string>
#include <fstream>
#include <regex>

class Reader {
protected:
    std::string file_path_;
    std::regex  dimension_regex_;
    std::regex  name_regex_;

    unsigned* adjacency_matrix_;
    
    int dimension_;

    bool allocateAdjacencyMatrixWith(const unsigned& size);
    void fetchDimension(std::ifstream& file_stream);
public:
    Reader(const std::string file_path);
    virtual ~Reader();
    
    unsigned* getAdjacencyMatrix();
    int getAdjacencyMatrixSize();

    virtual void prepare() noexcept(false) = 0;
    virtual void process() = 0;
};

#endif // define READER_READER_H
