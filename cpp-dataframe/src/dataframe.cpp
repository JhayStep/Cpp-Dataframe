
#include "cppdf/dataframe.hpp"
#include "cppdf/util.hpp"
#include <iostream>
#include <sstream>
#include <map>
#include <stdexcept>
#include <iomanip>

namespace cppdf {

size_t DataFrame::col_index(const std::string& name) const {
    for (size_t i = 0; i < columns.size(); ++i) if (columns[i] == name) return i;
    throw std::runtime_error("Column not found: " + name);
}

DataFrame DataFrame::select(const std::vector<std::string>& cols) const {
    DataFrame out;
    out.columns = cols;
    for (const auto& row : data) {
        std::vector<std::string> newrow;
        newrow.reserve(cols.size());
        for (const auto& c : cols) {
            newrow.push_back(row[col_index(c)]);
        }
        out.data.push_back(std::move(newrow));
    }
    return out;
}

static bool compare_vals(const std::string& a, const std::string& op, const std::string& b) {
    double da, db;
    bool na = try_parse_double(a, da);
    bool nb = try_parse_double(b, db);
    if (na && nb) {
        if (op == "==") return da == db;
        if (op == "!=") return da != db;
        if (op == ">")  return da >  db;
        if (op == ">=") return da >= db;
        if (op == "<")  return da <  db;
        if (op == "<=") return da <= db;
    } else {
        if (op == "==") return a == b;
        if (op == "!=") return a != b;
        if (op == ">")  return a >  b;
        if (op == ">=") return a >= b;
        if (op == "<")  return a <  b;
        if (op == "<=") return a <= b;
    }
    throw std::runtime_error("Unsupported operator: " + op);
}

DataFrame DataFrame::filter(const std::string& column, const std::string& op, const std::string& value) const {
    DataFrame out;
    out.columns = columns;
    size_t idx = col_index(column);
    for (const auto& row : data) {
        if (compare_vals(row[idx], op, value)) out.data.push_back(row);
    }
    return out;
}

DataFrame DataFrame::sort_by(const std::string& column) const {
    DataFrame out = *this;
    size_t idx = col_index(column);
    std::sort(out.data.begin(), out.data.end(), [&](const auto& a, const auto& b){
        return a[idx] < b[idx];
    });
    return out;
}

DataFrame DataFrame::groupby(const std::string& key, const std::vector<std::string>& aggs) const {
    size_t kidx = col_index(key);

    struct AggState {
        size_t count = 0;
        std::unordered_map<std::string, double> sum;
        std::unordered_map<std::string, size_t> sum_count;
    };

    std::map<std::string, AggState> buckets;

    // parse aggs
    std::vector<std::pair<std::string,std::string>> parsed; // (op, col)
    for (const auto& a : aggs) {
        auto parts = split_simple(a, ':');
        if (parts.size() != 2) throw std::runtime_error("Bad agg: " + a);
        parsed.push_back({trim(parts[0]), trim(parts[1])});
    }

    for (const auto& row : data) {
        auto& st = buckets[row[kidx]];
        st.count++;
        for (const auto& [op, col] : parsed) {
            if (op == "sum" || op == "mean") {
                if (col == "*") continue;
                size_t cidx = col_index(col);
                double v;
                if (try_parse_double(row[cidx], v)) {
                    st.sum[col] += v;
                    st.sum_count[col] += 1;
                }
            }
        }
    }

    // Build output
    DataFrame out;
    out.columns.push_back(key);
    for (const auto& [op, col] : parsed) {
        if (op == "count" && col == "*") out.columns.push_back("count");
        else out.columns.push_back(op + "(" + col + ")");
    }

    for (auto& [k, st] : buckets) {
        std::vector<std::string> r;
        r.push_back(k);
        for (const auto& [op, col] : parsed) {
            if (op == "count" && col == "*") {
                r.push_back(std::to_string(st.count));
            } else if (op == "sum") {
                std::ostringstream ss; ss << std::setprecision(12) << st.sum[col];
                r.push_back(ss.str());
            } else if (op == "mean") {
                double mean = st.sum_count[col] ? (st.sum[col] / st.sum_count[col]) : 0.0;
                std::ostringstream ss; ss << std::setprecision(12) << mean;
                r.push_back(ss.str());
            } else {
                throw std::runtime_error("Unsupported agg op: " + op);
            }
        }
        out.data.push_back(std::move(r));
    }

    return out;
}

void DataFrame::print_csv() const {
    for (size_t i = 0; i < columns.size(); ++i) {
        std::cout << columns[i];
        if (i + 1 < columns.size()) std::cout << ",";
    }
    std::cout << "\n";
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            std::cout << row[i];
            if (i + 1 < row.size()) std::cout << ",";
        }
        std::cout << "\n";
    }
}

} // namespace cppdf
