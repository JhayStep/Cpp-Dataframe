
add_executable(cppdf_tests test_dataframe.cpp)
target_link_libraries(cppdf_tests PRIVATE cppdf_lib)
add_test(NAME cppdf_tests COMMAND cppdf_tests)
