#ifndef READER_DISPLAY_DATA_READER_H
#define READER_DISPLAY_DATA_READER_H

#include <fstream>
#include <cstdint>

#include "../reader-interface/reader.h"

class DisplayDataReader final : public Reader {
private:
    std::ifstream file_stream_;
    uint8_t** adjacency_matrix_;
public:
    DisplayDataReader(const std::string& file_path);
    ~DisplayDataReader();

    void prepare() noexcept(false) override;
    void process() override;
};

#endif // define READER_DISPLAY_DATA_READER_H
