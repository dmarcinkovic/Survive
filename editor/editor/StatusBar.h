//
// Created by david on 26. 11. 2021..
//

#ifndef SURVIVE_STATUSBAR_H
#define SURVIVE_STATUSBAR_H

#include <functional>
#include <imgui.h>

#include "Texture.h"
#include "Loader.h"

namespace Survive
{
	using ButtonListener = std::function<void()>;

	class StatusBar
	{
	private:
		Texture m_PlayButton, m_ReloadButton;

		Loader m_Loader;

		bool m_IsScenePlaying{};

		std::vector<ButtonListener> m_PlayButtonListeners;
		std::vector<ButtonListener> m_ReloadButtonListeners;

	public:
		StatusBar();

		[[nodiscard]] bool isScenePlaying() const;

		void addPlayButtonListener(const ButtonListener &listener);

		void addReloadButtonListener(const ButtonListener &listener);

		void draw();

	private:
		void drawPlayAndPauseButtons(float buttonSize);

		static void setPlayButtonColorStyle();

		static void notifyListeners(const std::vector<ButtonListener> &listeners);

		static bool drawImageButton(const Texture &image, bool disabled, const ImVec2 &buttonSize,
									const std::vector<ButtonListener> &buttonListener, const char *tooltipText);
	};
}


#endif //SURVIVE_STATUSBAR_H
