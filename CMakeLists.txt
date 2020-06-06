cmake_minimum_required(VERSION 3.15)
project(Survive)

set(CMAKE_CXX_STANDARD 20)

set(OpenGlLinkers -lGLU -lGL -lGLEW)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(GLEW REQUIRED STATIC)

add_executable(Survive main.cpp engine/texture/stb_image.h engine/texture/stb_image.cpp engine/display/Display.cpp engine/display/Display.h engine/renderer/Loader.cpp engine/renderer/Loader.h engine/shader/Shader.cpp engine/shader/Shader.h engine/texture/TexturedModel.cpp engine/texture/TexturedModel.h engine/renderer/Renderer2D.cpp engine/renderer/Renderer2D.h engine/entity/Entity.cpp engine/entity/Entity.h engine/gui/GuiShader.cpp engine/gui/GuiShader.h engine/gui/GuiRenderer.cpp engine/gui/GuiRenderer.h engine/math/Maths.cpp engine/math/Maths.h engine/text/Text.cpp engine/text/Text.h engine/text/TextShader.cpp engine/text/TextShader.h engine/text/TextRenderer.cpp engine/text/TextRenderer.h engine/text/Character.cpp engine/text/Character.h engine/text/Font.cpp engine/text/Font.h engine/util/Util.cpp engine/util/Util.h engine/renderer/Renderer2DUtil.cpp engine/renderer/Renderer2DUtil.h engine/ui/button/ButtonShader.cpp engine/ui/button/ButtonShader.h engine/ui/button/Button.cpp engine/ui/button/Button.h engine/ui/button/ButtonRenderer.cpp engine/ui/button/ButtonRenderer.h engine/obj/ObjLoader.cpp engine/obj/ObjLoader.h engine/objects/ObjectShader.cpp engine/objects/ObjectShader.h engine/camera/Camera.cpp engine/camera/Camera.h engine/objects/ObjectRenderer.cpp engine/objects/ObjectRenderer.h engine/renderer/Renderer3DUtil.cpp engine/renderer/Renderer3DUtil.h engine/light/Light.cpp engine/light/Light.h engine/objects/Object3D.cpp engine/objects/Object3D.h engine/renderer/Renderer3D.cpp engine/renderer/Renderer3D.h engine/texture/Texture.cpp engine/texture/Texture.h)

target_link_libraries(Survive ${OpenGlLinkers})

include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(Survive ${GLFW_LIBRARIES})
target_link_libraries(Survive ${OPENGL_LIBRARIES} ${GLFW3_LIBRARY} ${GLEW_LIBRARY})