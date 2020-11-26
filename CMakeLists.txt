cmake_minimum_required(VERSION 3.17)
project(Lab_optim_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab_optim_3 main.cpp simplex.cpp simplex.h integer_LP.h full_enumeration.h max_F.h)