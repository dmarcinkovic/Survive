//
// Created by david on 08. 01. 2021..
//

#ifndef SURVIVE_EVENTHANDLER_H
#define SURVIVE_EVENTHANDLER_H

#include <array>

#include "Key.h"

namespace Survive
{
	class EventHandler
	{
	private:
		static constexpr int NUMBER_OF_KEYS = 350;

		std::array<bool, NUMBER_OF_KEYS> m_Keys{};

	public:
		EventHandler();

		[[nodiscard]] bool isKeyPressed(Key key) const;

		[[nodiscard]] bool isKeyControlPressed() const;

		[[nodiscard]] bool isShiftKeyPressed() const;

	private:
		void addKeyboardListener();
	};
}


#endif //SURVIVE_EVENTHANDLER_H
