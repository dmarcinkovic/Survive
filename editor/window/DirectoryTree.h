//
// Created by david on 26. 08. 2021..
//

#ifndef SURVIVE_DIRECTORYTREE_H
#define SURVIVE_DIRECTORYTREE_H

#include <imgui.h>
#include <stack>
#include <vector>
#include <filesystem>
#include <functional>

#include "FileUtil.h"

namespace Survive
{
	using Listener = std::function<void(std::filesystem::path, std::vector<File>)>;

	class DirectoryTree
	{
	private:
		std::stack<std::filesystem::path> m_RedoStack;
		std::filesystem::path m_CurrentDirectory;

		std::vector<File> m_DirectoryContent;
		std::vector<std::vector<File>> m_NestedDirectories;
		std::vector<Listener> m_Listeners;

	public:
		DirectoryTree(std::filesystem::path currentDirectory, std::vector<File> directoryContent);

		void drawTree();

		void addListener(const Listener &listener);

		[[nodiscard]] const std::filesystem::path &getCurrentDirectory() const;

		[[nodiscard]] const std::vector<File> &getDirectoryContent() const;

		void setCurrentDirectory(std::filesystem::path currentDirectory);

	private:
		static void setStyleColors();

		void drawDirectoryTree();

		void drawArrows();

		void drawLeftArrow();

		void drawRightArrow();

		static ImGuiTreeNodeFlags getTreeFlags(std::filesystem::file_type type);

		static void drawNestedDirectories(std::vector<File> &content, const File &file);

		void informListeners() const;
	};
}

#endif //SURVIVE_DIRECTORYTREE_H
