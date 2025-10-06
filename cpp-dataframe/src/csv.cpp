
#include "cppdf/csv.hpp"
#include "cppdf/util.hpp"
#include <fstream>
#include <stdexcept>

namespace cppdf {

CsvTable read_csv(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Failed to open CSV: " + path);

    CsvTable t;
    std::string line;
    if (!std::getline(in, line)) throw std::runtime_error("Empty CSV: " + path);
    t.header = split_simple(line, ',');

    while (std::getline(in, line)) {
        auto parts = split_simple(line, ',');
        // normalize to header size
        if (parts.size() < t.header.size()) parts.resize(t.header.size());
        t.rows.push_back(std::move(parts));
    }
    return t;
}

} // namespace cppdf
