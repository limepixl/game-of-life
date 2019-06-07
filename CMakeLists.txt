cmake_minimum_required(VERSION 3.14)

project(game_of_life)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
