cmake_minimum_required(VERSION 3.17)
project(game)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(game main.cpp Game.cpp Game.h State.cpp State.h)

target_link_libraries(game sfml-graphics sfml-audio)