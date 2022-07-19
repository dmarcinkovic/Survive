//
// Created by david on 10.07.22..
//

#include <fstream>

#include "ScriptEditor.h"

void Survive::ScriptEditor::render()
{
	bool validFile = m_CurrentFile.has_filename() && exists(m_CurrentFile) && is_regular_file(m_CurrentFile);

	if (m_DrawScriptEditor)
	{
		if (ImGui::Begin("Script Editor", &m_DrawScriptEditor) && validFile)
		{
			m_WindowHasFocus = ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows);

			const ImGuiTabBarFlags tabBarFlags = ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_AutoSelectNewTabs;
			if (ImGui::BeginTabBar("Script Filename tab", tabBarFlags))
			{
				drawTabs();
				ImGui::EndTabBar();
			}
		}
		ImGui::End();
	}
}

void Survive::ScriptEditor::createScript(const std::filesystem::path &path)
{
	if (openScriptIfAlreadyExists(path))
	{
		return;
	}

	std::ifstream reader(path.string());

	if (reader)
	{
		TextEditor textEditor;
		textEditor.SetLanguageDefinition(TextEditor::LanguageDefinition::CPlusPlus());

		std::string content((std::istreambuf_iterator<char>(reader)), std::istreambuf_iterator<char>());
		textEditor.SetText(content);

		m_SelectedTab = static_cast<int>(m_Scripts.size());
		m_Scripts.emplace_back(Script{.textEditor = textEditor, .path = path, .opened = true});

		m_DrawScriptEditor = true;
		m_CurrentFile = path;
	}
}

void Survive::ScriptEditor::handleKeyEvents(const EventHandler &eventHandler)
{
	bool sKeyReleased = m_SKeyWasPressed && !eventHandler.isKeyPressed(Key::S);
	bool selectedTabValid = m_CurrentTab >= 0 && m_CurrentTab < m_Scripts.size();

	if (m_WindowHasFocus && eventHandler.isKeyControlPressed() && sKeyReleased && selectedTabValid)
	{
		const TextEditor &textEditor = m_Scripts[m_CurrentTab].textEditor;

		if (textEditor.CanUndo())
		{
			std::ofstream writer(m_Scripts[m_CurrentTab].path.string());

			if (writer)
			{
				writer << textEditor.GetText();
				writer.close();
			}
		}
	}

	m_SKeyWasPressed = eventHandler.isKeyPressed(Key::S);
}

Survive::ScriptEditor &Survive::ScriptEditor::getInstance()
{
	static ScriptEditor scriptEditor;
	return scriptEditor;
}

bool Survive::ScriptEditor::openScriptIfAlreadyExists(const std::filesystem::path &path)
{
	for (int i = 0; i < m_Scripts.size(); ++i)
	{
		Script &script = m_Scripts[i];

		if (script.path == path)
		{
			m_SelectedTab = i;
			m_DrawScriptEditor = true;
			m_CurrentFile = path;

			return true;
		}
	}

	return false;
}

void Survive::ScriptEditor::drawTabs()
{
	for (int i = 0; i < m_Scripts.size(); ++i)
	{
		Script &script = m_Scripts[i];

		const std::string title = script.path.string();
		const std::string label = title + "##Script";

		ImGuiTabItemFlags tabItemFlags = m_SelectedTab == i ? ImGuiTabItemFlags_SetSelected : ImGuiTabItemFlags_None;
		if (script.textEditor.CanUndo())
		{
			tabItemFlags |= ImGuiTabItemFlags_UnsavedDocument;
		}

		if (ImGui::BeginTabItem(label.c_str(), &script.opened, tabItemFlags))
		{
			m_SelectedTab = -1;
			m_CurrentTab = i;

			script.textEditor.Render(title.c_str());
			ImGui::EndTabItem();
		}
	}
}

bool Survive::ScriptEditor::isUsingKeyEvents() const
{
	return m_WindowHasFocus;
}
