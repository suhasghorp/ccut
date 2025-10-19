#include "ccut/options.hpp"
#include "ccut/field_extractor.hpp"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    auto opts = ccut::parseArgs(argc, argv);
    if (!opts.has_value()) {
        std::cerr << "Error: " << opts.error() << std::endl;
        return 1;
    }
    
    std::ifstream file(opts->filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file '" << opts->filename << "'" << std::endl;
        return 1;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        auto result = ccut::FieldExtractor::extractFields(line, opts->delimiter, opts->fields);
        if (!result.has_value()) {
            std::cerr << "Error: " << result.error() << std::endl;
            return 1;
        }
        
        // Print the extracted fields
        for (size_t i = 0; i < result->size(); ++i) {
            if (i > 0) {
                std::cout << opts->delimiter;
            }
            std::cout << (*result)[i];
        }
        std::cout << std::endl;
    }
    
    return 0;
}
