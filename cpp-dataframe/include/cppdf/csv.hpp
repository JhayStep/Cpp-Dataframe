
#pragma once
#include <string>
#include <vector>

namespace cppdf {

struct CsvTable {
    std::vector<std::string> header;
    std::vector<std::vector<std::string>> rows; // rows x cols
};

// Minimal CSV reader: no quoted commas support for brevity.
CsvTable read_csv(const std::string& path);

} // namespace cppdf
