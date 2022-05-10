cmake_minimum_required(VERSION 3.18)
project(pybind_vid)
add_subdirectory(pybind11)
pybind11_add_module(module_name python.cpp)
