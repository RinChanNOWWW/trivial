cmake_minimum_required(VERSION 3.9)

project(trivial VERSION 1.0.0 DESCRIPTION "contains some useful cpp codes")

set(CMAKE_CXX_STANDARD 11)

install(FILES include/trivial/algorithm.h include/trivial/strings.h
  DESTINATION /usr/local/include/trivial)