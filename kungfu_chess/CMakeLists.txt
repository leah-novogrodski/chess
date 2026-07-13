cmake_minimum_required(VERSION 3.20)

project(kungfu_chess
        VERSION 1.0
        LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# =========================
# Main application
# =========================

file(GLOB_RECURSE GAME_SOURCES
        src/*.cpp
)


add_executable(kungfu_chess
        ${GAME_SOURCES}
)


target_include_directories(kungfu_chess
        PRIVATE
        include
)


# =========================
# Tests
# =========================

enable_testing()


file(GLOB_RECURSE TEST_SOURCES
        tests/*.cpp
)


# לא להכניס main.cpp של המשחק לטסטים
list(REMOVE_ITEM TEST_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)


add_executable(test_runner

        ${TEST_SOURCES}

        # קוד המקור של המשחק
        src/model/board.cpp
        src/model/game_state.cpp
        src/model/piece.cpp
        src/model/position.cpp

        src/io/board_parser.cpp
        src/io/board_printer.cpp

        src/input/board_mapper.cpp
        src/input/controller.cpp

        src/engine/game_engine.cpp

        src/rules/piece_rules.cpp
        src/rules/rule_engine.cpp

        src/realtime/motion.cpp
        src/realtime/real_time_arbiter.cpp

        src/view/image_view.cpp
)


target_include_directories(test_runner
        PRIVATE
        include
        tests
)


add_test(
        NAME chess_tests
        COMMAND test_runner
)