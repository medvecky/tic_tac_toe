cmake_minimum_required(VERSION 3.10)
project(tic_tac_toe C)

set(CMAKE_C_STANDARD 99)

add_executable(tic_tac_toe main.c boardView.c boardModel.c boardController.c tic_tac_toe.h)