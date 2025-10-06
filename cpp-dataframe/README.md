
# cpp-dataframe

A modern C++17 DataFrame-style CSV analytics library with a tiny CLI. It supports:

- Reading CSVs with headers
- Selecting columns
- Row filtering with simple predicates
- Group-by with `sum`, `count`, `mean` aggregations
- Sorting results
- Unit tests (Catch2 single-header vendored)
- CMake build system

> Designed as a resume-ready project showing clean architecture, testing, and documentation.

## Build

```bash
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j
ctest --output-on-failure
```

## CLI Usage

```bash
./cppdf --input examples/sample.csv --select Country,Year,Population         --filter "Year>=2010"         --groupby Country --agg count:*,mean:Population         --sort Country
```

### Flags

- `--input <path>`: CSV with header row.
- `--select <c1,c2,...>`: Optional projection.
- `--filter "<Column><op><value>"`: One predicate; ops: `==`, `!=`, `>`, `>=`, `<`, `<=` (numeric if possible).
- `--groupby <Column>`: Group key.
- `--agg a1,a2,...`: Aggregations like `sum:Col`, `mean:Col`, `count:*`.
- `--sort <Column>`: Sort ascending by column in output.

### Examples

```bash
# 1) Just select two columns
./cppdf --input examples/sample.csv --select Country,Population

# 2) Filter and select
./cppdf --input examples/sample.csv --filter "Population>=500" --select Country,Population

# 3) Group by and aggregate
./cppdf --input examples/sample.csv --groupby Country --agg count:*,sum:Population,mean:Population

# 4) End-to-end
./cppdf --input examples/sample.csv --select Country,Year,Population         --filter "Year>=2010" --groupby Country --agg mean:Population --sort Country
```

## Project Structure

```
cpp-dataframe/
├── CMakeLists.txt
├── README.md
├── LICENSE
├── include/
│   └── cppdf/
│       ├── csv.hpp
│       ├── dataframe.hpp
│       ├── groupby.hpp
│       └── util.hpp
├── src/
│   ├── csv.cpp
│   ├── dataframe.cpp
│   ├── groupby.cpp
│   └── main.cpp
├── tests/
│   ├── CMakeLists.txt
│   ├── catch.hpp
│   └── test_dataframe.cpp
└── examples/
    └── sample.csv
```

## Notes

- CSV parser is minimal and assumes no quoted commas; it's easy to extend.
- Numeric operations try to parse as `double`; non-numeric values are treated as `NaN` (ignored in `sum`/`mean`).

## License

MIT
