cmake_minimum_required(VERSION 3.14)
project(chess_game CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build the doctest test suite" ON)
option(USE_LOCAL_OPENCV "Use local OpenCV in OpenCV_451 folder" ON)

function(configure_opencv target)
    if(USE_LOCAL_OPENCV)
        set(OPENCV_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/view/OpenCV_451")
        if(EXISTS "${OPENCV_ROOT}/include" AND (EXISTS "${OPENCV_ROOT}/bin/opencv_world451.lib" OR EXISTS "${OPENCV_ROOT}/bin/opencv_world451d.lib"))
            message(STATUS "Using local OpenCV at ${OPENCV_ROOT}")
            target_include_directories(${target} PRIVATE "${OPENCV_ROOT}/include")
            set(OPENCV_LIBRARY "$<IF:$<CONFIG:Debug>,${OPENCV_ROOT}/bin/opencv_world451d.lib,${OPENCV_ROOT}/bin/opencv_world451.lib>")
            target_link_libraries(${target} PRIVATE ${OPENCV_LIBRARY})

            add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "$<IF:$<CONFIG:Debug>,${OPENCV_ROOT}/bin/opencv_world451d.dll,${OPENCV_ROOT}/bin/opencv_world451.dll>"
                    $<TARGET_FILE_DIR:${target}>
            )
        else()
            message(FATAL_ERROR "Local OpenCV not found in ${OPENCV_ROOT}. Please ensure the include and bin directories exist.")
        endif()
    else()
        find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
        if(OpenCV_FOUND)
            target_include_directories(${target} PRIVATE ${OpenCV_INCLUDE_DIRS})
            target_link_libraries(${target} PRIVATE ${OpenCV_LIBS})
        endif()
    endif()
endfunction()

add_executable(chess_game
    main.cpp
    model/Board.cpp
    model/Piece.cpp
    model/Position.cpp
    rules/PieceRules.cpp
    rules/RuleEngine.cpp
    realtime/RealTimeArbiter.cpp
    input/BoardMapper.cpp
    input/Controller.cpp
    engine/GameEngine.cpp
    texttests/ScriptRunner.cpp
    io/BoardParser.cpp
    io/BoardPrinter.cpp
    view/img.cpp
)
target_include_directories(chess_game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/view)
configure_opencv(chess_game)

add_executable(sprite_demo
    sprite_demo.cpp
    view/img.cpp
    view/SpriteLoader.cpp
    view/renderer.cpp
    io/BoardParser.cpp
    model/Board.cpp
    model/Piece.cpp
    model/Position.cpp
    realtime/RealTimeArbiter.cpp
    rules/PieceRules.cpp
    engine/GameEngine.cpp
rules/RuleEngine.cpp
    engine/GameSnapshot.cpp
)
target_include_directories(sprite_demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/view)
configure_opencv(sprite_demo)

if(BUILD_TESTS)
    enable_testing()

    add_executable(chess_tests
        tests/doctest_main.cpp
        tests/Config.tests.cpp
        tests/Board.tests.cpp
        tests/Movement.tests.cpp
        tests/Engine.tests.cpp
        tests/Piece.tests.cpp
        model/Board.cpp
        model/Piece.cpp
        model/Position.cpp
        rules/PieceRules.cpp
        rules/RuleEngine.cpp
        realtime/RealTimeArbiter.cpp
        input/BoardMapper.cpp
        input/Controller.cpp
        engine/GameEngine.cpp
        texttests/ScriptRunner.cpp
        io/BoardParser.cpp
        io/BoardPrinter.cpp
    )
    target_include_directories(chess_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} third_party)
    configure_opencv(chess_tests)

    add_test(NAME chess_tests COMMAND chess_tests)

    option(ENABLE_COVERAGE "Build chess_tests with coverage instrumentation" OFF)

    if(ENABLE_COVERAGE)
        target_compile_options(chess_tests PRIVATE --coverage -O0 -g)
        target_link_options(chess_tests PRIVATE --coverage)
    endif()
endif()

