cmake_minimum_required(VERSION 3.6)
project(cpp_workspace)
set(CMAKE_CXX_STANDARD 11)


#set(SOURCE_FILES OJ/OJ/Ali/alitest.cpp)
#set(SOURCE_FILES OJ/OJ/io.cpp)
#set(SOURCE_FILES JustForTest/JustForTest/JustForTest.cpp OJ/OJ/Ali/t1.cpp)
#set(SOURCE_FILES /home/pipi/files/mine/cpp_workspace/OJ/OJ/test.cpp)
#set(SOURCE_FILES /home/pipi/files/mine/cpp_workspace/JustForTest/JustForTest/bitsetTest.cpp)
set(SOURCE_FILES /home/pipi/files/mine/cpp_workspace/OJ/OJ/Ali/t1.cpp OJ/OJ/Ali/TopologicalSort.cpp OJ/OJ/Ali/WordReverse.cpp OJ/OJ/Ali/AlpahbetPath.cpp OJ/OJ/Ali/t2.cpp OJ/OJ/Indeed/Locating.cpp)

add_executable(cpp_workspace ${SOURCE_FILES})
