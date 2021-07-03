//
// Created by david on 08. 01. 2021..
//

#ifndef SURVIVE_EVENTHANDLER_H
#define SURVIVE_EVENTHANDLER_H

namespace Survive
{
	class EventHandler
	{
	private:
		int m_Key{};

	public:
		EventHandler();

		[[nodiscard]] int getKeyPressed() const;

		static bool isKeyControlPressed() ;

	private:
		void addKeyboardListener();
	};
}


#endif //SURVIVE_EVENTHANDLER_H
