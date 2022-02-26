//
// Created by david on 07. 03. 2021..
//

#ifndef SURVIVE_LOGEDITOR_H
#define SURVIVE_LOGEDITOR_H

#include <string>
#include <imgui.h>
#include <utility>
#include <vector>

#include "Texture.h"
#include "Loader.h"
#include "Log.h"

namespace Survive
{
	class LogEditor : public Log
	{
	private:
		static constexpr int ITEMS_VISIBLE = 10;

		Loader m_Loader;

		Texture m_ErrorIcon;
		Texture m_InfoIcon;
		Texture m_WarnIcon;

	public:
		LogEditor();

		void drawLogWindow();

	private:
		void drawIcon(LogType logType) const;
	};
}


#endif //SURVIVE_LOGEDITOR_H
