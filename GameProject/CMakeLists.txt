cmake_minimum_required (VERSION 3.20)

project("GameProject")

set(RESOURCE "${CMAKE_SOURCE_DIR}/Moon/Resources/Moon.rc")

add_executable(${PROJECT_NAME} ${RESOURCE} "main.cpp" "Scene/BlankScene.cpp" "Characters/King.cpp" "Assets/King/KingIdle.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/Moon" "${CMAKE_SOURCE_DIR}/GameProject")

target_link_libraries(${PROJECT_NAME} "Moon")