cmake_minimum_required(VERSION 3.23)
project(ex1 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex1 main.c data.c tree.c item.c st.c)
