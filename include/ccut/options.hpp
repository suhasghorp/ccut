#pragma once

#include <expected>
#include <string>
#include <vector>

namespace ccut {

struct Options {
    std::vector<size_t> fields;
    char delimiter = '\t';
    std::string filename;
};

std::expected<Options, std::string> parseArgs(int argc, char* argv[]);

} // namespace ccut
