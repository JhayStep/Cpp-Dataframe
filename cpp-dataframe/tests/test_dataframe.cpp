
#include "cppdf/csv.hpp"
#include "cppdf/dataframe.hpp"
#include <cassert>
#include <sstream>
#include <fstream>

using namespace cppdf;

static void write_sample(const std::string& path) {
    std::ofstream o(path);
    o << "Country,Year,Population\n";
    o << "USA,2010,309\n";
    o << "USA,2020,331\n";
    o << "Canada,2010,34\n";
    o << "Canada,2020,38\n";
}

int main() {
    // Prepare temp CSV
    std::string path = "test_sample.csv";
    write_sample(path);

    auto csv = read_csv(path);
    DataFrame df; df.columns = csv.header; df.data = csv.rows;

    // select
    auto s = df.select({"Country","Population"});
    assert(s.columns.size() == 2);
    assert(s.data.size() == 4);

    // filter
    auto f = df.filter("Year", ">=", "2015");
    assert(f.data.size() == 2);

    // groupby mean
    auto g = df.groupby("Country", {"mean:Population","count:*"});
    assert(g.data.size() == 2);

    // sort
    auto so = g.sort_by("Country");
    assert(so.data[0][0] == "Canada");
    assert(so.data[1][0] == "USA");

    return 0;
}
