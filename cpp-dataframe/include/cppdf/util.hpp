
#pragma once
#include <string>
#include <vector>
#include <optional>
#include <algorithm>
#include <cctype>

namespace cppdf {

inline std::string trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t\n\r");
    auto end = s.find_last_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    return s.substr(start, end - start + 1);
}

inline std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> out;
    std::string cur;
    for (char c : s) {
        if (c == delim) {
            out.push_back(cur);
            cur.clear();
        } else {
            out.push_back(std::string(1, c)).swap(cur); // placeholder
            cur.push_back(c);
            cur.pop_back(); // fix silly swap
            cur.push_back(c);
        }
    }
    // The above got messy; simpler:
    out.clear(); cur.clear();
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == delim) {
            out.push_back(cur);
            cur.clear();
        } else {
            cur.push_back(s[i]);
        }
    }
    out.push_back(cur);
    return out;
}

inline std::vector<std::string> split_simple(const std::string& s, char delim) {
    std::vector<std::string> out;
    std::string cur;
    for (char c : s) {
        if (c == delim) { out.push_back(cur); cur.clear(); }
        else { cur.push_back(c); }
    }
    out.push_back(cur);
    return out;
}

inline bool try_parse_double(const std::string& s, double& out) {
    try {
        size_t idx = 0;
        out = std::stod(trim(s), &idx);
        return idx == trim(s).size();
    } catch (...) {
        return false;
    }
}

} // namespace cppdf
