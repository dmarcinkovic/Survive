cmake_minimum_required(VERSION 3.15)
project(Survive)

set(CMAKE_CXX_STANDARD 20)

set(OpenGlLinkers -lGLU -lGL -lGLEW)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(GLEW REQUIRED STATIC)

add_executable(Survive main.cpp stb_image.h stb_image.cpp engine/display/Display.cpp engine/display/Display.h)

target_link_libraries(Survive ${OpenGlLinkers})

include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(Survive ${GLFW_LIBRARIES})
target_link_libraries(Survive ${OPENGL_LIBRARIES} ${GLFW3_LIBRARY} ${GLEW_LIBRARY})