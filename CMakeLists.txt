cmake_minimum_required(VERSION 3.5.1)
project(YouTubeDownloader
        VERSION 1.0.0
        LANGUAGES CXX)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
add_executable(dijkstra dijkstra.cpp)
add_executable(LevelOrderTraversal LevelOrderTraversal.cpp)
add_executable(BalanceBracket BalanceBracket.cpp)
add_executable(RunningMedian RunningMedian.cpp)
add_executable(test_x test.cpp)