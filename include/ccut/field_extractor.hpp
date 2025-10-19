#pragma once

#include <expected>
#include <string>
#include <string_view>
#include <vector>

namespace ccut {

class FieldExtractor {
public:
    static std::expected<std::vector<std::string>, std::string> 
    extractFields(std::string_view line, char delimiter, const std::vector<size_t>& fieldIndices);
};

} // namespace ccut
