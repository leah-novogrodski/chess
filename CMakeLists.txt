cmake_minimum_required(VERSION 3.14)
project(chess_game CXX)

include(FetchContent)

if(POLICY CMP0169)
    cmake_policy(SET CMP0169 OLD)
endif()

FetchContent_Declare(
    websocketpp
    GIT_REPOSITORY https://github.com/zaphoyd/websocketpp.git
    GIT_TAG        master
)
FetchContent_GetProperties(websocketpp)
if(NOT websocketpp_POPULATED)
    FetchContent_Populate(websocketpp)
endif()

FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG        asio-1-30-2
)
FetchContent_GetProperties(asio)
if(NOT asio_POPULATED)
    FetchContent_Populate(asio)
endif()

set(WEBSOCKETPP_INCLUDE_DIR ${websocketpp_SOURCE_DIR})
set(ASIO_INCLUDE_DIR ${asio_SOURCE_DIR}/asio/include)

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

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
)
FetchContent_GetProperties(nlohmann_json)
if(NOT nlohmann_json_POPULATED)
    FetchContent_Populate(nlohmann_json)
endif()

set(NLOHMANN_JSON_INCLUDE_DIR ${nlohmann_json_SOURCE_DIR}/single_include)

add_executable(chess_game
   main.cpp
   view/img.cpp
    view/SpriteLoader.cpp
    view/Renderer.cpp
    model/Board.cpp
    model/Piece.cpp
    model/Position.cpp
    rules/PieceRules.cpp
    rules/RuleEngine.cpp
    realtime/RealTimeArbiter.cpp
    input/BoardMapper.cpp
    input/Controller.cpp
    io/BoardParser.cpp
    engine/GameSnapshot.cpp
    engine/GameEngine.cpp
)
target_include_directories(chess_game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/view)
configure_opencv(chess_game)

if(USE_LOCAL_OPENCV)
    if(EXISTS "${OPENCV_ROOT}/include" AND (EXISTS "${OPENCV_ROOT}/bin/opencv_world451.lib" OR EXISTS "${OPENCV_ROOT}/bin/opencv_world451d.lib"))
        target_include_directories(live_demo PRIVATE "${OPENCV_ROOT}/include")
        target_link_libraries(live_demo PRIVATE ${OPENCV_LIBRARY})

        add_custom_command(TARGET live_demo POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<IF:$<CONFIG:Debug>,${OPENCV_ROOT}/bin/opencv_world451d.dll,${OPENCV_ROOT}/bin/opencv_world451.dll>"
                $<TARGET_FILE_DIR:live_demo>
        )
    endif()
else()
    if(OpenCV_FOUND)
        target_include_directories(live_demo PRIVATE ${OpenCV_INCLUDE_DIRS})
        target_link_libraries(live_demo PRIVATE ${OpenCV_LIBS})
    endif()
endif()

add_executable(sprite_demo
    sprite_demo.cpp
    view/img.cpp
    view/SpriteLoader.cpp
    view/Renderer.cpp
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

add_executable(ws_echo_server network/ws_echo_server.cpp)
add_executable(ws_echo_client network/ws_echo_client.cpp)

foreach(ws_target ws_echo_server ws_echo_client)
    target_include_directories(${ws_target} PRIVATE ${WEBSOCKETPP_INCLUDE_DIR} ${ASIO_INCLUDE_DIR})
    target_compile_definitions(${ws_target} PRIVATE
        ASIO_STANDALONE             # standalone (non-Boost) Asio mode
        _WEBSOCKETPP_CPP11_STL_     # tell websocketpp to use std:: (not Boost) where it auto-detects C++11
        _WEBSOCKETPP_CPP11_THREAD_  # websocketpp assumes MinGW lacks C++11 <thread>/<mutex> by default
                                    # (true for very old MinGW32); this MinGW toolchain has full support,
                                    # so force it rather than silently falling back to requiring Boost.Thread
    )

    if(WIN32)
        # Asio needs to know the target Windows API version on MinGW, or it
        # errors out at compile time; Winsock libraries are needed for the
        # actual socket calls it makes.
        target_compile_definitions(${ws_target} PRIVATE _WIN32_WINNT=0x0601)
        target_link_libraries(${ws_target} PRIVATE ws2_32 wsock32 mswsock)
    endif()
endforeach()

