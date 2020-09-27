cmake_minimum_required(VERSION 3.15)
project(Survive)

set(CMAKE_CXX_STANDARD 20)

set(OpenGlLinkers -lGLU -lGL -lGLEW -lopenal)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(GLEW REQUIRED STATIC)

add_executable(Survive main.cpp engine/texture/stb_image.h engine/texture/stb_image.cpp engine/display/Display.cpp engine/display/Display.h engine/renderer/Loader.cpp engine/renderer/Loader.h engine/shader/Shader.cpp engine/shader/Shader.h engine/texture/Texture.cpp engine/texture/Texture.h engine/audio/Source.cpp engine/audio/Source.h engine/audio/AudioMaster.cpp engine/audio/AudioMaster.h engine/renderer/Renderer2D.cpp engine/renderer/Renderer2D.h engine/entity/Entity.cpp engine/entity/Entity.h engine/gui/GuiShader.cpp engine/gui/GuiShader.h engine/gui/GuiRenderer.cpp engine/gui/GuiRenderer.h engine/math/Maths.cpp engine/math/Maths.h engine/text/Text.cpp engine/text/Text.h engine/text/TextShader.cpp engine/text/TextShader.h engine/text/TextRenderer.cpp engine/text/TextRenderer.h engine/text/Character.cpp engine/text/Character.h engine/text/Font.cpp engine/text/Font.h engine/util/Util.cpp engine/util/Util.h engine/renderer/Renderer2DUtil.cpp engine/renderer/Renderer2DUtil.h engine/ui/button/ButtonShader.cpp engine/ui/button/ButtonShader.h engine/ui/button/Button.cpp engine/ui/button/Button.h engine/ui/button/ButtonRenderer.cpp engine/ui/button/ButtonRenderer.h engine/parser/ObjParser.cpp engine/parser/ObjParser.h engine/objects/ObjectShader.cpp engine/objects/ObjectShader.h engine/camera/Camera.cpp engine/camera/Camera.h engine/objects/ObjectRenderer.cpp engine/objects/ObjectRenderer.h engine/renderer/Renderer3DUtil.cpp engine/renderer/Renderer3DUtil.h engine/light/Light.cpp engine/light/Light.h engine/objects/Object3D.cpp engine/objects/Object3D.h engine/renderer/Renderer3D.cpp engine/renderer/Renderer3D.h engine/fbo/FrameBuffer.cpp engine/fbo/FrameBuffer.h engine/shadowMapping/ShadowShader.cpp engine/shadowMapping/ShadowShader.h engine/shadowMapping/ShadowRenderer.cpp engine/shadowMapping/ShadowRenderer.h engine/terrain/Terrain.cpp engine/terrain/Terrain.h engine/terrain/TerrainShader.cpp engine/terrain/TerrainShader.h engine/terrain/TerrainRenderer.cpp engine/terrain/TerrainRenderer.h engine/texture/TexturedModel.cpp engine/texture/TexturedModel.h engine/constant/Constants.h engine/parser/DaeParser.cpp engine/parser/DaeParser.h engine/animation/joints/Joint.cpp engine/animation/joints/Joint.h engine/animation/AnimationRenderer.cpp engine/animation/AnimationRenderer.h engine/animation/AnimationShader.cpp engine/animation/AnimationShader.h engine/math/Quaternion.cpp engine/math/Quaternion.h engine/animation/joints/JointTransform.cpp engine/animation/joints/JointTransform.h engine/physics/World.cpp engine/physics/World.h engine/physics/collision/BodyType.h engine/physics/collision/Body.cpp engine/physics/collision/Body.h)

target_link_libraries(Survive ${OpenGlLinkers})

include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(Survive ${GLFW_LIBRARIES})
target_link_libraries(Survive ${OPENGL_LIBRARIES} ${GLFW3_LIBRARY} ${GLEW_LIBRARY})