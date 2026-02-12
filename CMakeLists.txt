cmake_minimum_required(VERSION 3.16)
project(Chess++)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(chess++
    main.cpp
    board.cpp
    game.cpp
    king.cpp
    queen.cpp
    rook.cpp
    bishop.cpp
    knight.cpp
    pawn.cpp
    player.cpp
    Io.cpp
)

if(WIN32)
    target_compile_definitions(chess++ PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
