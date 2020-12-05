cmake_minimum_required(VERSION 3.17)
project(game)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/sources/*.cpp")

add_executable(game main.cpp ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(game sfml-graphics sfml-audio sfml-window sfml-system)