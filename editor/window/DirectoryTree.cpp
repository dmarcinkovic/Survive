//
// Created by david on 26. 08. 2021..
//

#include "DirectoryTree.h"
#include "Log.h"
#include "EditorUtil.h"

Survive::DirectoryTree::DirectoryTree(std::filesystem::path currentDirectory, std::vector<File> directoryContent)
		: m_CurrentDirectory(std::move(currentDirectory)), m_DirectoryContent(std::move(directoryContent)),
		  m_NestedDirectories(m_DirectoryContent.size()), m_IsCollapsed(m_DirectoryContent.size(), false)
{

}

void Survive::DirectoryTree::drawTree()
{
	drawArrows();

	ImGui::BeginChild("Child1");

	setStyleColors();

	drawDirectoryTree();

	ImGui::PopStyleColor(2);
	ImGui::EndChild();
}

void Survive::DirectoryTree::setStyleColors()
{
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.05f, 0.05f, 0.05f, 1.0f));
}

void Survive::DirectoryTree::drawArrows()
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1, 0.2, 0.3, 1));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0.1f, 0.2f, 1));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.25f, 0.3f, 0.45f, 1));

	drawLeftArrow();
	ImGui::SameLine();
	drawRightArrow();

	ImGui::PopStyleColor(3);
}

void Survive::DirectoryTree::drawLeftArrow()
{
	bool disabled = EditorUtil::disableButton(m_CurrentDirectory == m_CurrentDirectory.root_path());

	if (ImGui::ArrowButton("Back arrow", ImGuiDir_Left))
	{
		try
		{
			m_DirectoryContent = FileUtil::listDirectory(m_CurrentDirectory.parent_path().string());
			m_IsCollapsed = std::vector<bool>(m_DirectoryContent.size(), false);

			m_RedoStack.push(m_CurrentDirectory);
			m_CurrentDirectory = m_CurrentDirectory.parent_path();

			m_NestedDirectories = std::vector<std::vector<File>>(m_DirectoryContent.size());

			informListeners();
		} catch (const std::filesystem::filesystem_error &exception)
		{
			const std::string &path = m_CurrentDirectory.parent_path().string();
			Log::logWindow(LogType::ERROR, "Cannot enter directory: " + path);
		}
	}

	EditorUtil::enableButton(disabled);
}

void Survive::DirectoryTree::drawRightArrow()
{
	bool disabled = EditorUtil::disableButton(m_RedoStack.empty());

	if (ImGui::ArrowButton("Forward arrow", ImGuiDir_Right))
	{
		m_CurrentDirectory = m_RedoStack.top();

		m_DirectoryContent = FileUtil::listDirectory(m_CurrentDirectory.string());
		m_IsCollapsed = std::vector<bool>(m_DirectoryContent.size(), false);

		m_NestedDirectories = std::vector<std::vector<File>>(m_DirectoryContent.size());
		m_RedoStack.pop();

		informListeners();
	}

	EditorUtil::enableButton(disabled);
}

ImGuiTreeNodeFlags Survive::DirectoryTree::getTreeFlags(std::filesystem::file_type type)
{
	if (type == std::filesystem::file_type::directory)
	{
		return ImGuiTreeNodeFlags_None;
	}

	return ImGuiTreeNodeFlags_Leaf;
}

void
Survive::DirectoryTree::drawNestedDirectories(std::vector<File> &content, const Survive::File &file, bool collapsed)
{
	if (content.empty() && !collapsed)
	{
		try
		{
			content = FileUtil::listDirectory(file.path.string());
		} catch (const std::filesystem::filesystem_error &exception)
		{
			Log::logWindow(LogType::ERROR, "Cannot collapse " + file.path.string());
		}
	}

	for (const File &nestedFile: content)
	{
		std::string filename = nestedFile.path.filename().string();
		if (ImGui::TreeNodeEx(filename.c_str(), ImGuiTreeNodeFlags_Leaf))
		{
			ImGui::TreePop();
		}
	}
}

void Survive::DirectoryTree::drawDirectoryTree()
{
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);

	std::string directory = getCurrentDirectoryFilename();
	if (ImGui::TreeNode(directory.c_str()))
	{
		for (int i = 0; i < m_DirectoryContent.size(); ++i)
		{
			const File &file = m_DirectoryContent[i];
			ImGuiTreeNodeFlags flags = getTreeFlags(file.type);
			std::string filename = file.path.filename().string();

			if (ImGui::TreeNodeEx(filename.c_str(), flags))
			{
				if (file.type == std::filesystem::file_type::directory)
				{
					drawNestedDirectories(m_NestedDirectories[i], file, m_IsCollapsed[i]);
					m_IsCollapsed[i] = true;
				}

				ImGui::TreePop();
			} else
			{
				m_IsCollapsed[i] = false;
			}
		}

		ImGui::TreePop();
	}
}

const std::vector<Survive::File> &Survive::DirectoryTree::getDirectoryContent() const
{
	return m_DirectoryContent;
}

void Survive::DirectoryTree::setCurrentDirectory(const std::filesystem::path &currentDirectory)
try
{
	m_DirectoryContent = FileUtil::listDirectory(currentDirectory.string());
	m_IsCollapsed = std::vector<bool>(m_DirectoryContent.size(), false);
	m_CurrentDirectory = currentDirectory;

	m_NestedDirectories = std::vector<std::vector<File>>(m_DirectoryContent.size());
} catch (const std::filesystem::filesystem_error &error)
{
	Log::logWindow(LogType::ERROR, "Cannot enter directory: " + currentDirectory.string());
}

void Survive::DirectoryTree::addListener(const Survive::DirectoryListener &listener)
{
	m_Listeners.emplace_back(listener);
}

void Survive::DirectoryTree::informListeners() const
{
	for (const DirectoryListener &listener: m_Listeners)
	{
		listener(m_CurrentDirectory, m_DirectoryContent);
	}
}

std::string Survive::DirectoryTree::getCurrentDirectoryFilename() const
{
	if (m_CurrentDirectory.has_filename())
	{
		return m_CurrentDirectory.filename().string();
	}
	return m_CurrentDirectory.string();
}
