#include "ccut/field_extractor.hpp"
#include <ranges>

namespace ccut {

std::expected<std::vector<std::string>, std::string> 
FieldExtractor::extractFields(std::string_view line, char delimiter, const std::vector<size_t>& fieldIndices) {
    if (line.empty()) {
        return std::vector<std::string>{};
    }
    
    // Split the line by delimiter using ranges
    auto fields = line | std::views::split(delimiter) | std::views::transform([](auto&& range) {
        return std::string(range.begin(), range.end());
    });
    
    std::vector<std::string> fieldVec(fields.begin(), fields.end());
    
    // Extract requested fields
    std::vector<std::string> result;
    for (size_t index : fieldIndices) {
        if (index >= fieldVec.size()) {
            return std::unexpected("Field " + std::to_string(index + 1) + " does not exist");
        }
        result.push_back(fieldVec[index]);
    }
    
    return result;
}

} // namespace ccut
