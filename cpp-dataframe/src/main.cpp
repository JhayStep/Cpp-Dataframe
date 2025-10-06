
#include "cppdf/csv.hpp"
#include "cppdf/dataframe.hpp"
#include "cppdf/util.hpp"
#include <iostream>
#include <unordered_map>

using namespace cppdf;

struct Args {
    std::string input;
    std::vector<std::string> select;
    std::optional<std::string> filter_col, filter_op, filter_val;
    std::optional<std::string> groupby;
    std::vector<std::string> aggs;
    std::optional<std::string> sort;
};

static Args parse_args(int argc, char** argv) {
    Args a;
    std::unordered_map<std::string,std::string> kv;
    for (int i = 1; i < argc; ++i) {
        std::string s = argv[i];
        if (s == "--input" && i + 1 < argc) a.input = argv[++i];
        else if (s == "--select" && i + 1 < argc) a.select = split_simple(argv[++i], ',');
        else if (s == "--filter" && i + 1 < argc) {
            std::string f = argv[++i];
            // parse like "Col>=10"
            const char* ops[] = {"==","!=",">=","<=",">","<"};
            std::string opfound;
            size_t pos = std::string::npos;
            for (auto& op : ops) {
                pos = f.find(op);
                if (pos != std::string::npos) { opfound = op; break; }
            }
            if (opfound.empty()) throw std::runtime_error("Bad --filter format. Use Col>=Value");
            a.filter_col = trim(f.substr(0, pos));
            a.filter_op  = opfound;
            a.filter_val = trim(f.substr(pos + opfound.size()));
        }
        else if (s == "--groupby" && i + 1 < argc) a.groupby = argv[++i];
        else if (s == "--agg" && i + 1 < argc) a.aggs = split_simple(argv[++i], ',');
        else if (s == "--sort" && i + 1 < argc) a.sort = argv[++i];
        else {
            // ignore unknown for brevity
        }
    }
    if (a.input.empty()) throw std::runtime_error("--input is required");
    return a;
}

int main(int argc, char** argv) {
    try {
        auto args = parse_args(argc, argv);
        auto csv = read_csv(args.input);

        DataFrame df; df.columns = csv.header; df.data = csv.rows;

        if (!args.select.empty()) df = df.select(args.select);
        if (args.filter_col) df = df.filter(*args.filter_col, *args.filter_op, *args.filter_val);
        if (args.groupby) df = df.groupby(*args.groupby, args.aggs);
        if (args.sort) df = df.sort_by(*args.sort);

        df.print_csv();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        std::cerr << "Usage: ./cppdf --input file.csv [--select c1,c2] [--filter "Col>=Val"] [--groupby Col --agg a1,a2] [--sort Col]\n";
        return 1;
    }
}
