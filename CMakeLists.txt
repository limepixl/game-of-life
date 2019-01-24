cmake_minimum_required(VERSION 3.8)

project(game_of_life)

set(SFML_DIR "usr/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES FALSE)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
add_executable(game_of_life main.cpp)
target_link_libraries(game_of_life sfml-graphics)
