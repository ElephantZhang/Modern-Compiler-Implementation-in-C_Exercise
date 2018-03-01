cmake_minimum_required(VERSION 3.9)
project(KyomaCompiler)

set(CMAKE_CXX_STANDARD 17)

add_executable(KyomaCompiler main.cpp languageTree.h util.h chapter1ProgrammingExercise.cpp)