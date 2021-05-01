//
// Created by david on 08. 03. 2020..
//

#include <iostream>

#include "Display.h"
#include "../math/Maths.h"
#include "../constant/Constants.h"

std::vector<Survive::KeyListener> Survive::Display::m_KeyEventListeners;
std::vector<Survive::MouseListener> Survive::Display::m_MouseEventListeners;
std::vector<Survive::MouseMovedListener> Survive::Display::m_MouseMoveListeners;
std::vector<Survive::WindowListener> Survive::Display::m_WindowListeners;
std::vector<Survive::ScrollListener> Survive::Display::m_ScrollListeners;

double Survive::Display::m_LastFrameTime{};
double Survive::Display::m_DeltaTime{};

int Survive::Display::m_Width;
int Survive::Display::m_Height;

Survive::Display::Display(int width, int height, const char *title)
{
	glfwInit();

	setWindowHints();

	m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);

	glewInit();

	addCallbacks();

	m_LastFrameTime = glfwGetTime();

	m_Width = width;
	m_Height = height;

	setProjectionMatrices(width, height);
	setStencilProperties();
}

void Survive::Display::addCallbacks() const
{
	glfwSetWindowSizeCallback(m_Window, windowResizeCallback);
	glfwSetMouseButtonCallback(m_Window, mouseEventCallback);
	glfwSetKeyCallback(m_Window, keyEventCallback);
	glfwSetCursorPosCallback(m_Window, mousePositionCallback);
	glfwSetScrollCallback(m_Window, scrollCallback);
}

Survive::Display::~Display()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
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

void Survive::Display::windowResizeCallback(GLFWwindow *, int width, int height)
{
	setViewport(width, height);

	m_Width = width;
	m_Height = height;

	for (auto const &listener : m_WindowListeners)
	{
		listener(width, height);
	}

	setProjectionMatrices(width, height);
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

void Survive::Display::keyEventCallback(GLFWwindow *, int key, int, int action, int)
{
	for (auto const &listener : m_KeyEventListeners)
	{
		listener(key, action);
	}
}

void Survive::Display::mouseEventCallback(GLFWwindow *window, int button, int action, int)
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	for (auto const &listener : m_MouseEventListeners)
	{
		listener(button, action, mouseX, mouseY);
	}
}

void Survive::Display::addKeyListener(const KeyListener &listener)
{
	m_KeyEventListeners.emplace_back(listener);
}

void Survive::Display::addMouseListener(const MouseListener &listener)
{
	m_MouseEventListeners.emplace_back(listener);
}

double Survive::Display::getFrameTime()
{
	return m_DeltaTime;
}

void Survive::Display::mousePositionCallback(GLFWwindow *, double mouseX, double mouseY)
{
	for (auto const &listener : m_MouseMoveListeners)
	{
		listener(mouseX, mouseY);
	}
}

void Survive::Display::addMouseMovedListener(const MouseMovedListener &listener)
{
	m_MouseMoveListeners.emplace_back(listener);
}

void Survive::Display::addWindowResizeListener(const WindowListener &listener)
{
	m_WindowListeners.emplace_back(listener);
}

void Survive::Display::scrollCallback(GLFWwindow *, double xOffset, double yOffset)
{
	for (auto const &listener : m_ScrollListeners)
	{
		listener(xOffset, yOffset);
	}
}

void Survive::Display::addScrollListener(const ScrollListener &listener)
{
	m_ScrollListeners.emplace_back(listener);
}

void Survive::Display::setProjectionMatrices(int width, int height)
{
	Maths::projectionMatrix = Maths::createProjectionMatrix(Constants::FOV);
	Maths::lightProjectionMatrix = Maths::createLightProjectionMatrix();

	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	Maths::orthographicProjectionMatrix = Maths::createOrthographicProjectionMatrix(aspectRatio, 1.0f);
}

void Survive::Display::setStencilProperties()
{
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
}

int Survive::Display::getWidth()
{
	return m_Width;
}

int Survive::Display::getHeight()
{
	return m_Height;
}
