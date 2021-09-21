//
// Created by david on 08. 03. 2020..
//

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Display.h"
#include "Constants.h"
#include "Maths.h"

double Survive::Display::m_LastFrameTime{};
double Survive::Display::m_DeltaTime{};

int Survive::Display::m_Width;
int Survive::Display::m_Height;

Survive::Display::Display(int width, int height, const char *title)
{
	glfwInit();
	setWindowHints();

	init(width, height, title);
}

Survive::Display::Display(const char *title)
{
	glfwInit();
	setWindowHints();

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *mode = glfwGetVideoMode(monitor);

	init(mode->width, mode->height, title);
}

void Survive::Display::init(int width, int height, const char *title)
{
	m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);

	glewInit();
	addCallbacks();
	addListener();
	initializeImGui();

	m_LastFrameTime = glfwGetTime();

	m_Width = width;
	m_Height = height;

	setStencilProperties();
}

Survive::Display::~Display()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Survive::Display::addCallbacks() const
{
	glfwSetWindowSizeCallback(m_Window, EventHandler::windowResizeCallback);
	glfwSetMouseButtonCallback(m_Window, EventHandler::mouseEventCallback);
	glfwSetKeyCallback(m_Window, EventHandler::keyEventCallback);
	glfwSetCursorPosCallback(m_Window, EventHandler::mousePositionCallback);
	glfwSetScrollCallback(m_Window, EventHandler::scrollCallback);
}

void Survive::Display::update() const
{
	double currentTime = glfwGetTime();
	m_DeltaTime = currentTime - m_LastFrameTime;
	m_LastFrameTime = currentTime;

	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

bool Survive::Display::isRunning() const
{
	return !glfwWindowShouldClose(m_Window);
}

void Survive::Display::clearWindow()
{
	glm::vec4 clearColor = Constants::CLEAR_COLOR;
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);

	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_STENCIL_BUFFER_BIT);
}

void Survive::Display::setWindowHints()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Survive::Display::setViewport(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, width, 0, height, -1.5, 1.5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

double Survive::Display::getFrameTime()
{
	return m_DeltaTime;
}

void Survive::Display::setStencilProperties()
{
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
}

void Survive::Display::initializeImGui()
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
}

int Survive::Display::getWidth()
{
	return m_Width;
}

int Survive::Display::getHeight()
{
	return m_Height;
}

std::pair<int, int> Survive::Display::getMaxViewportSize()
{
	static GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	static const GLFWvidmode *mode = glfwGetVideoMode(monitor);

	return {mode->width, mode->height};
}

void Survive::Display::addListener()
{
	auto listener = [](int width, int height) {
		setViewport(width, height);

		m_Width = width;
		m_Height = height;
	};

	EventHandler::addWindowResizeListener(listener);
}
