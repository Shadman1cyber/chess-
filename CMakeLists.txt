cmake_minimum_required(VERSION 3.16)
project(Chess++)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(chess++
    src/main.cpp
    src/piece.cpp
    src/board.cpp
    src/game.cpp
    src/king.cpp
    src/queen.cpp
    src/rook.cpp
    src/bishop.cpp
    src/knight.cpp
    src/pawn.cpp
    src/player.cpp
    src/Io.cpp
)

if(WIN32)
    target_compile_definitions(chess++ PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
