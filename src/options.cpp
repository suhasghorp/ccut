#include "ccut/options.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>

namespace ccut {

std::expected<Options, std::string> parseArgs(int argc, char* argv[]) {
    Options opts;
    
    if (argc < 2) {
        return std::unexpected("Usage: ccut -f<fields> [-d<delimiter>] <file>");
    }
    
    // Parse arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg.starts_with("-f")) {
            // Extract field specification
            std::string fieldSpec = arg.substr(2);
            if (fieldSpec.empty()) {
                return std::unexpected("Field specification required after -f");
            }
            
            // Parse field specification (comma or space separated)
            std::vector<std::string> fieldSpecs;
            
            // Check if it contains spaces (space-separated) or commas (comma-separated)
            if (fieldSpec.find(' ') != std::string::npos) {
                // Split by spaces
                std::istringstream iss(fieldSpec);
                std::string field;
                while (iss >> field) {
                    fieldSpecs.push_back(field);
                }
            } else {
                // Split by commas
                std::istringstream iss(fieldSpec);
                std::string field;
                while (std::getline(iss, field, ',')) {
                    fieldSpecs.push_back(field);
                }
            }
            
            // Parse each field number
            for (const auto& spec : fieldSpecs) {
                size_t fieldNum = 0;
                bool valid = true;
                for (char c : spec) {
                    if (c < '0' || c > '9') {
                        valid = false;
                        break;
                    }
                    fieldNum = fieldNum * 10 + static_cast<size_t>(c - '0');
                }
                
                if (!valid || fieldNum == 0) {
                    return std::unexpected("Invalid field number: " + spec);
                }
                
                opts.fields.push_back(fieldNum - 1); // Convert to 0-indexed
            }
        }
        else if (arg.starts_with("-d")) {
            // Extract delimiter
            std::string delimSpec = arg.substr(2);
            if (delimSpec.length() != 1) {
                return std::unexpected("Delimiter must be exactly one character");
            }
            opts.delimiter = delimSpec[0];
        }
        else if (!arg.starts_with("-")) {
            // This is the filename
            opts.filename = arg;
        }
        else {
            return std::unexpected("Unknown option: " + arg);
        }
    }
    
    if (opts.filename.empty()) {
        return std::unexpected("No filename specified");
    }
    
    if (opts.fields.empty()) {
        return std::unexpected("No fields specified");
    }
    
    return opts;
}

} // namespace ccut
