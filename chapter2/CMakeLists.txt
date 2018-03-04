cmake_minimum_required(VERSION 3.9)
project(chapter2 C)

set(CMAKE_C_STANDARD 99)

add_executable(chapter2 driver.c errormsg.c errormsg.h tokens.h util.c util.h)