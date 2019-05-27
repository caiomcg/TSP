#include <iostream>

#include "reader/reader-factory/reader-factory.h"

int main(int argc, char** argv) {
    (void) argc; // unused parameter

    try {
        auto reader = ReaderFactory().createReader(argv[1]);
        reader->prepare();
        reader->process();
    } catch (const std::exception& e) {
        std::clog << "Failed - what(): " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
