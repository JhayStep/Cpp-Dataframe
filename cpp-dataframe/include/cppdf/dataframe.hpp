
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

namespace cppdf {

struct DataFrame {
    std::vector<std::string> columns;
    std::vector<std::vector<std::string>> data; // rows x cols

    size_t col_index(const std::string& name) const;
    DataFrame select(const std::vector<std::string>& cols) const;
    DataFrame filter(const std::string& column, const std::string& op, const std::string& value) const;
    DataFrame sort_by(const std::string& column) const;

    // Groupby single key with aggregations like { "count:*", "sum:Population", "mean:Population" }
    DataFrame groupby(const std::string& key,
                      const std::vector<std::string>& aggregations) const;

    // Utility to print as CSV to stdout
    void print_csv() const;
};

} // namespace cppdf
