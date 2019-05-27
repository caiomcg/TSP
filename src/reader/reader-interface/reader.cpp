#include "reader.h"

Reader::Reader(const std::string file_path) : file_path_{file_path}, 
    dimension_regex_{R"((DIMENSION):\ (\d+))"}, name_regex_{R"((NAME): (.+))"} {}

Reader::~Reader() {}

