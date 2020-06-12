cmake_minimum_required(VERSION 3.15)
project(Survive)

set(CMAKE_CXX_STANDARD 20)

set(OpenGlLinkers -lGLU -lGL -lGLEW -lopenal)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(GLEW REQUIRED STATIC)

add_executable(Survive main.cpp engine/texture/stb_image.h engine/texture/stb_image.cpp engine/display/Display.cpp engine/display/Display.h engine/renderer/Loader.cpp engine/renderer/Loader.h engine/shader/Shader.cpp engine/shader/Shader.h engine/texture/Texture.cpp engine/texture/Texture.h engine/audio/Source.cpp engine/audio/Source.h engine/audio/AudioMaster.cpp engine/audio/AudioMaster.h)

target_link_libraries(Survive ${OpenGlLinkers})

include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(Survive ${GLFW_LIBRARIES})
target_link_libraries(Survive ${OPENGL_LIBRARIES} ${GLFW3_LIBRARY} ${GLEW_LIBRARY})