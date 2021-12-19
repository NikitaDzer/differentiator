cmake_minimum_required(VERSION 3.20)
project(differentiator)

set(CMAKE_CXX_STANDARD 14)

add_executable(differentiator main.cpp src/differentiator.cpp include/differentiator.h src/tree.cpp include/tree.h src/dump.cpp include/dump.h include/config.h src/hash.cpp include/hash.h src/parser.cpp include/parser.h src/optimizer.cpp include/optimizer.h src/tex.cpp include/tex.h)
