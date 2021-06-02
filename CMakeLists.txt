cmake_minimum_required(VERSION 3.19)
project(NonlinearEquations)

set(CMAKE_CXX_STANDARD 14)

include_directories(headers)

add_executable(NonlinearEquations
        headers/matrix.h
        headers/NonLinearSolver.h
        source/matrix.cpp
        source/NonLinearSolver.cpp
        main.cpp source/NonLinearSystemSolver.cpp headers/NonLinearSystemSolver.h source/LinearEquationSystemSolver.cpp headers/LinearEquationSystemSolver.h)
