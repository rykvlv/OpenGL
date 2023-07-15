cmake_minimum_required(VERSION 3.5)

project(OpenGL VERSION 1.0)

link_directories(${CMAKE_SOURCE_DIR}/lib)

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/OpenGL/*.cpp" "${CMAKE_SOURCE_DIR}/OpenGL/*.c")

add_executable(OpenGL ${SOURCE_FILES})

target_link_libraries(OpenGL PUBLIC glfw3.lib opengl32.lib)
target_include_directories(OpenGL PUBLIC include)