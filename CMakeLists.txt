cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_BUILD_TYPE "Debug") 
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
## load in pkg-config support
include_directories(src)
add_executable(a.out src/main.cpp)
