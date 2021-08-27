//
// Created by david on 26. 08. 2021..
//

#ifndef SURVIVE_DIRECTORYTREE_H
#define SURVIVE_DIRECTORYTREE_H

#include <imgui.h>
#include <stack>
#include <vector>
#include <filesystem>

#include "FileUtil.h"

namespace Survive
{
	class DirectoryTree
	{
	private:
		std::stack<std::filesystem::path> m_RedoStack;
		std::filesystem::path m_CurrentDirectory;

		std::vector<File> m_DirectoryContent;
		std::vector<std::vector<File>> m_NestedDirectories;

		bool m_DirectoryChanged{};

	public:
		DirectoryTree(std::filesystem::path currentDirectory, std::vector<File> directoryContent);

		void drawTree();

		[[nodiscard]] const std::filesystem::path &getCurrentDirectory() const;

		[[nodiscard]] const std::vector<File> &getDirectoryContent() const;

		[[nodiscard]] bool directoryChanged() const;

		void setCurrentDirectory(std::filesystem::path currentDirectory);

	private:
		static void setStyleColors();

		void drawDirectoryTree();

		void drawArrows();

		void drawLeftArrow();

		void drawRightArrow();

		static ImGuiTreeNodeFlags getTreeFlags(std::filesystem::file_type type);

		static void drawNestedDirectories(std::vector<File> &content, const File &file);
	};
}

#endif //SURVIVE_DIRECTORYTREE_H
