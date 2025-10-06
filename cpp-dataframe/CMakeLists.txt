
cmake_minimum_required(VERSION 3.14)
project(cpp-dataframe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(cppdf_lib
    src/csv.cpp
    src/dataframe.cpp
    src/groupby.cpp
)

target_include_directories(cppdf_lib PUBLIC include)

add_executable(cppdf src/main.cpp)
target_link_libraries(cppdf PRIVATE cppdf_lib)

enable_testing()
add_subdirectory(tests)
