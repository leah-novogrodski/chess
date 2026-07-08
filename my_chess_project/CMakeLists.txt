find_package(doctest CONFIG REQUIRED)
target_link_libraries(your_target PRIVATE doctest::doctest)