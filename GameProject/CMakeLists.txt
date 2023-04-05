cmake_minimum_required (VERSION 3.20)

project("GameProject")

add_executable(${PROJECT_NAME} "main.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/Moon")


target_link_libraries(${PROJECT_NAME} "Moon")