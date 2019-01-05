cmake_minimum_required(VERSION 3.12)
project(210CT-COURSEWORK)

set(CMAKE_CXX_STANDARD 14)

add_executable(graph "Undirected_graph/undirectedGraph.h" Undirected_graph/linkedList.h)
add_executable(unit-testing "unit-testing.cpp")
