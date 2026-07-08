cmake_minimum_required(VERSION 3.16)
project(my_chess_project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/tests)

# Collect project sources (exclude src/main.cpp from the test runner)
file(GLOB_RECURSE PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
set(MAIN_SRC ${CMAKE_SOURCE_DIR}/src/main.cpp)
list(REMOVE_ITEM PROJECT_SOURCES ${MAIN_SRC})

# Optional main executable if present
if(EXISTS ${MAIN_SRC})
	add_executable(my_chess ${MAIN_SRC})
	target_include_directories(my_chess PRIVATE ${CMAKE_SOURCE_DIR}/include)
endif()

# Test runner: builds all source files (except main.cpp) plus tests/test_main.cpp
add_executable(test_runner ${PROJECT_SOURCES} ${CMAKE_SOURCE_DIR}/tests/test_main.cpp)
target_include_directories(test_runner PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/tests)

# If doctest is installed as a package, link it. Otherwise the single-header in tests/ will be used.
find_package(doctest CONFIG QUIET)
if(doctest_FOUND)
	target_link_libraries(test_runner PRIVATE doctest::doctest)
endif()

enable_testing()
add_test(NAME unit_tests COMMAND test_runner)

# Place build outputs in the same bin folder for convenience
set_target_properties(test_runner PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/tests/Debug
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/tests/Release
	RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/tests/RelWithDebInfo
	RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/tests/MinSizeRel
)
if(TARGET my_chess)
	set_target_properties(my_chess PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
		RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug
		RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release
	)
endif()