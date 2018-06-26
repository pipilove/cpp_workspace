cmake_minimum_required(VERSION 3.6)
project(cpp_workspace)
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES /home/pipi/files/mine/cpp_workspace/OJ/OJ/test.cpp OJ/OJ/DP/LCS.cpp OJ/OJ/DP/EditDistance.cpp)

add_executable(cpp_workspace ${SOURCE_FILES})
