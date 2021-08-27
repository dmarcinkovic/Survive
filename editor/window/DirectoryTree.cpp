//
// Created by david on 26. 08. 2021..
//

#include "DirectoryTree.h"

Survive::DirectoryTree::DirectoryTree(std::filesystem::path currentDirectory, std::vector<File> directoryContent)
		: m_CurrentDirectory(std::move(currentDirectory)), m_DirectoryContent(std::move(directoryContent)),
		  m_NestedDirectories(m_DirectoryContent.size())
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
	if (ImGui::ArrowButton("Back arrow", ImGuiDir_Left))
	{
		m_RedoStack.push(m_CurrentDirectory);
		m_CurrentDirectory = m_CurrentDirectory.parent_path();
		m_DirectoryContent = FileUtil::listDirectory(m_CurrentDirectory);

		informListeners();
	}
}

void Survive::DirectoryTree::drawRightArrow()
{
	if (ImGui::ArrowButton("Forward arrow", ImGuiDir_Right) && !m_RedoStack.empty())
	{
		m_CurrentDirectory = m_RedoStack.top();
		m_DirectoryContent = FileUtil::listDirectory(m_CurrentDirectory);
		m_RedoStack.pop();

		informListeners();
	}
}

ImGuiTreeNodeFlags Survive::DirectoryTree::getTreeFlags(std::filesystem::file_type type)
{
	if (type == std::filesystem::file_type::directory)
	{
		return ImGuiTreeNodeFlags_None;
	}

	return ImGuiTreeNodeFlags_Leaf;
}

void Survive::DirectoryTree::drawNestedDirectories(std::vector<File> &content, const Survive::File &file)
{
	if (content.empty())
	{
		content = FileUtil::listDirectory(file.path.string());
	}

	for (const File &nestedFile: content)
	{
		if (ImGui::TreeNodeEx(nestedFile.path.filename().c_str(), ImGuiTreeNodeFlags_Leaf))
		{
			ImGui::TreePop();
		}
	}
}

void Survive::DirectoryTree::drawDirectoryTree()
{
	ImGui::SetNextTreeNodeOpen(true, ImGuiCond_Once);

	if (ImGui::TreeNode(m_CurrentDirectory.filename().c_str()))
	{
		for (int i = 0; i < m_DirectoryContent.size(); ++i)
		{
			const File &file = m_DirectoryContent[i];
			ImGuiTreeNodeFlags flags = getTreeFlags(file.type);

			if (ImGui::TreeNodeEx(file.path.filename().c_str(), flags))
			{
				if (file.type == std::filesystem::file_type::directory)
				{
					drawNestedDirectories(m_NestedDirectories[i], file);
				}

				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}
}

const std::filesystem::path &Survive::DirectoryTree::getCurrentDirectory() const
{
	return m_CurrentDirectory;
}

const std::vector<Survive::File> &Survive::DirectoryTree::getDirectoryContent() const
{
	return m_DirectoryContent;
}

void Survive::DirectoryTree::setCurrentDirectory(std::filesystem::path currentDirectory)
{
	m_CurrentDirectory = std::move(currentDirectory);
	m_DirectoryContent = FileUtil::listDirectory(m_CurrentDirectory);
}

void Survive::DirectoryTree::addListener(const Survive::Listener &listener)
{
	m_Listeners.emplace_back(listener);
}

void Survive::DirectoryTree::informListeners() const
{
	for (const Listener &listener: m_Listeners)
	{
		listener(m_CurrentDirectory, m_DirectoryContent);
	}
}
