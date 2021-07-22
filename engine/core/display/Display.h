//
// Created by david on 08. 03. 2020..
//

#ifndef SURVIVE_DISPLAY_H
#define SURVIVE_DISPLAY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>

#include "EventHandler.h"

namespace Survive
{

	class Display
	{
	private:
		GLFWwindow *m_Window{};

		static double m_LastFrameTime;
		static double m_DeltaTime;

		static int m_Width, m_Height;

	public:
		Display(int width, int height, const char *title);

		explicit Display(const char* title);

		~Display();

		void update() const;

		static void clearWindow();

		[[nodiscard]] bool isRunning() const;

		static double getFrameTime();

		static std::pair<int, int> getMaxViewportSize();

		template<typename T>
		static std::pair<T, T> getWindowSize()
		{
			return {static_cast<T>(m_Width), static_cast<T>(m_Height)};
		}

		static int getWidth();

		static int getHeight();

	private:
		void init(int width, int height, const char *title);

		void initializeImGui();

		void addCallbacks() const;

		static void addListener() ;

		static void setViewport(int width, int height);

		static void setWindowHints();

		static void setStencilProperties();
	};
}

#endif //SURVIVE_DISPLAY_H
