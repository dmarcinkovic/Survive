//
// Created by david on 10.07.22..
//

#ifndef SURVIVE_SCRIPTEDITOR_H
#define SURVIVE_SCRIPTEDITOR_H

#include <vector>
#include <filesystem>
#include <TextEditor.h>

#include "EventHandler.h"

namespace Survive
{
	struct Script
	{
		TextEditor textEditor;
		std::filesystem::path path;
		bool opened{};
	};

	class ScriptEditor
	{
	private:
		std::vector<Script> m_Scripts;
		bool m_DrawScriptEditor{};

		std::filesystem::path m_CurrentFile;

		bool m_SKeyWasPressed{};
		bool m_WindowHasFocus{};
		int m_SelectedTab{-1};

	public:
		void render();

		void handleKeyEvents(const EventHandler &eventHandler);

		void createScript(const std::filesystem::path &path);

		ScriptEditor(const ScriptEditor &) = delete;

		static ScriptEditor &getInstance();

	private:
		ScriptEditor() = default;

		bool openScriptIfAlreadyExists(const std::filesystem::path &path);

		void drawTabs();
	};
}

#endif //SURVIVE_SCRIPTEDITOR_H
