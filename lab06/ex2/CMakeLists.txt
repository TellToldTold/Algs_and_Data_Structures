cmake_minimum_required(VERSION 3.23)
project(ex2 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex2 client.c util.c item.c stack.c)
