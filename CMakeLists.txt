cmake_minimum_required(VERSION 3.14)
project(Rattle)

set(CMAKE_CXX_STANDARD 14)

if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif ()
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif ()

FILE(GLOB TARGET_H "${CMAKE_SOURCE_DIR}/src/*/*.hpp")
FILE(GLOB TARGET_CPP "${CMAKE_SOURCE_DIR}/src/*/*.cpp")
SET(TARGET_SRC ${TARGET_CPP} ${TARGET_H})

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Token.hpp
        src/Lexer.cpp src/Lexer.hpp src/Parser.cpp src/Parser.hpp src/BinNode.hpp src/Interpreter.cpp src/Interpreter.hpp)
