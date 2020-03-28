cmake_minimum_required(VERSION 3.15)
project(Survive)

set(CMAKE_CXX_STANDARD 20)

set(OpenGlLinkers -lGLU -lGL -lGLEW)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(GLEW REQUIRED STATIC)

add_executable(Survive main.cpp engine/texture/stb_image.h engine/texture/stb_image.cpp engine/display/Display.cpp engine/display/Display.h engine/renderer/Loader.cpp engine/renderer/Loader.h engine/shader/Shader.cpp engine/shader/Shader.h engine/texture/Texture.cpp engine/texture/Texture.h engine/renderer/Renderer2D.cpp engine/renderer/Renderer2D.h engine/entity/Entity2D.cpp engine/entity/Entity2D.h engine/gui/GuiShader.cpp engine/gui/GuiShader.h engine/gui/GuiRenderer.cpp engine/gui/GuiRenderer.h math/Maths.cpp math/Maths.h)

target_link_libraries(Survive ${OpenGlLinkers})

include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(Survive ${GLFW_LIBRARIES})
target_link_libraries(Survive ${OPENGL_LIBRARIES} ${GLFW3_LIBRARY} ${GLEW_LIBRARY})