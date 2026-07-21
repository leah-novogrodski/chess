cmake_minimum_required(VERSION 3.14)
project(chess_game CXX C)

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

set(WEBSOCKETPP_INCLUDE_DIR ${websocketpp_SOURCE_DIR})

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

set(NLOHMANN_JSON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/json/single_include)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

set(SQLITE3_SOURCE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/sqlite)
FetchContent_Declare(
    picosha2
    GIT_REPOSITORY https://github.com/okdshin/PicoSHA2.git
    GIT_TAG        master
)
FetchContent_GetProperties(picosha2)
if(NOT picosha2_POPULATED)
    FetchContent_Populate(picosha2)
endif()
set(PICOSHA2_INCLUDE_DIR ${picosha2_SOURCE_DIR})

option(USE_LOCAL_OPENCV "Use local OpenCV in OpenCV_451 folder" OFF)

if(USE_LOCAL_OPENCV)
    set(OPENCV_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/OpenCV_451-20260714T084200Z-1-001/OpenCV_451")
    if(EXISTS "${OPENCV_ROOT}/include" AND (EXISTS "${OPENCV_ROOT}/bin/opencv_world451.lib" OR EXISTS "${OPENCV_ROOT}/bin/opencv_world451d.lib"))
        message(STATUS "Using local OpenCV at ${OPENCV_ROOT}")
        set(OPENCV_LIBRARY "$<IF:$<CONFIG:Debug>,${OPENCV_ROOT}/bin/opencv_world451d.lib,${OPENCV_ROOT}/bin/opencv_world451.lib>")
    else()
        message(WARNING "Local OpenCV not found under ${OPENCV_ROOT}; disable USE_LOCAL_OPENCV or place OpenCV there")
    endif()
else()
    find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
endif()

function(link_opencv target_name)
    if(USE_LOCAL_OPENCV)
        if(EXISTS "${OPENCV_ROOT}/include" AND (EXISTS "${OPENCV_ROOT}/bin/opencv_world451.lib" OR EXISTS "${OPENCV_ROOT}/bin/opencv_world451d.lib"))
            target_include_directories(${target_name} PRIVATE "${OPENCV_ROOT}/include")
            target_link_libraries(${target_name} PRIVATE ${OPENCV_LIBRARY})
            add_custom_command(TARGET ${target_name} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "$<IF:$<CONFIG:Debug>,${OPENCV_ROOT}/bin/opencv_world451d.dll,${OPENCV_ROOT}/bin/opencv_world451.dll>"
                    $<TARGET_FILE_DIR:${target_name}>
            )
        endif()
    else()
        if(OpenCV_FOUND)
            target_include_directories(${target_name} PRIVATE ${OpenCV_INCLUDE_DIRS})
            target_link_libraries(${target_name} PRIVATE ${OpenCV_LIBS})
        endif()
    endif()
endfunction()


function(copy_assets target_name)
    add_custom_command(TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:${target_name}>/assets"
    )
endfunction()

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
add_executable(game_server
    network/game_server.cpp
    network/protocol/JsonCodec.cpp
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
    persistence/Database.cpp
    persistence/UserRepository.cpp
    ${SQLITE3_SOURCE_DIR}/sqlite3.c
)
target_include_directories(game_server PRIVATE ${WEBSOCKETPP_INCLUDE_DIR} ${ASIO_INCLUDE_DIR} ${NLOHMANN_JSON_INCLUDE_DIR} ${SQLITE3_SOURCE_DIR} ${PICOSHA2_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(game_server PRIVATE ASIO_STANDALONE)

add_executable(game_client
    network/game_client.cpp
    network/protocol/JsonCodec.cpp
    view/img.cpp
    view/SpriteLoader.cpp
    view/Renderer.cpp
    audio/AudioPlayer.cpp
    audio/GameEventDetector.cpp
    network/win32_ui/LoginWindow.cpp
)
target_include_directories(
    game_client
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/view
    ${WEBSOCKETPP_INCLUDE_DIR}
    ${ASIO_INCLUDE_DIR}
    ${NLOHMANN_JSON_INCLUDE_DIR}
    
)

configure_opencv(game_client)
target_link_libraries(game_client PRIVATE winmm)

add_custom_command(TARGET game_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:game_client>/assets"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)