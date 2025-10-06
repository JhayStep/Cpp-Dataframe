# 📊 cpp-dataframe

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![CMake](https://img.shields.io/badge/build%20system-CMake-informational)](https://cmake.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Status](https://img.shields.io/badge/status-stable-success)]()

> A modern **C++17 DataFrame analytics library** for CSV data — supports filtering, selection, grouping, aggregation, and sorting.  
> Designed to demonstrate clean code architecture, CLI tooling, and software engineering practices.

---

## Overview

**cpp-dataframe** is a lightweight C++17 library and CLI tool that lets you perform **data manipulation operations** similar to Python’s Pandas — but written in modern, portable C++.  

It supports:
- Reading CSV files with headers
- Selecting specific columns
- Filtering rows with relational operators
- Group-by with `sum`, `mean`, and `count` aggregations
- Sorting results
- Command-line interface with clear options
- Unit testing with CMake integration

---

## ⚙️ Features

Modern **C++17** codebase  
**CMake** build system  
Modular headers (`csv.hpp`, `dataframe.hpp`, `util.hpp`)  
**CLI app**: `cppdf` for quick data queries  
Includes **unit tests** for reliability  
Cross-platform (Linux, macOS, Windows)

---

## 🧩 Project Structure

CLI Options
Flag	Description
--input <path>	Path to CSV file
--select <cols>	Comma-separated columns to include
--filter "<col><op><val>"	Filter condition (==, !=, >, >=, <, <=)
--groupby <col>	Column to group data by
--agg <ops>	Aggregations (sum:Col, mean:Col, count:*)
--sort <col>	Sort results ascendingTechnologies Used

C++17 STL

CMake

Streams / File I/O

Custom CSV Parser

Unit Testing

CLI Argument Parsing

🧾 License

This project is released under the MIT License
.

Author

Jhaydn Steplight
Saint Martin’s University – Computer Science
Passionate about software engineering, data systems, and clean C++ design.
