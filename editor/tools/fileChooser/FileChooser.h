//
// Created by david on 06. 12. 2020..
//

#ifndef SURVIVE_FILECHOOSER_H
#define SURVIVE_FILECHOOSER_H


#include <filesystem>
#include <string>
#include <vector>
#include <stack>
#include <functional>

#include "ConfirmWindow.h"
#include "FileUtil.h"
#include "Loader.h"

namespace Survive
{
	class FileChooser
	{
	private:
		static constexpr ImGuiTableFlags tableFlags =
				ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable |
				ImGuiTableFlags_Sortable |
				ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_Reorderable |
				ImGuiTableFlags_ScrollY;

		static constexpr float CONFIRM_WIDTH = 400.0f;
		static constexpr float CONFIRM_HEIGHT = 80.0f;
		static constexpr int BUFFER_SIZE = 255;

		Loader m_Loader;

		std::filesystem::path m_CurrentDirectory;
		const std::filesystem::path m_Root;

		ImTextureID m_Icon{};
		int m_SelectedFile = -1;

		std::vector<File> m_DirectoryContent;
		bool m_Hidden{};
		bool m_Previous{};

		std::string m_SelectedFileName;
		std::stack<std::filesystem::path> m_Undo;
		std::stack<std::filesystem::path> m_Redo;

		bool m_OpenedFile{};
		ConfirmWindow m_ConfirmWindow;

	public:
		FileChooser();

		void open(float windowWidth, float windowHeight, bool *open);

		void save(float windowWidth, float windowHeight, bool *open);

		[[nodiscard]] std::filesystem::path getSelectedFile() const;

		[[nodiscard]] std::string getSelectedFilename() const;

	private:
		static void setupDarkStyleColors();

		void drawNavigationArrows();

		void drawLeftArrow();

		void drawRightArrow();

		void drawUpArrow();

		void drawCheckbox();

		void drawSaveFilenameTextbox(bool *open);

		void drawOpenFilenameTextbox(bool *open);

		void drawTable(float windowHeight, bool *open, bool openAction);

		void drawHeader();

		static void drawCancelButton(bool *open);

		static void helpMarker(const char *description);

		void resetSelectedFile();

		void drawIcon();

		void fillTableRow(const File &file, int index, bool *open, bool openAction);

		void openPressed(bool *open);

		void savePressed(bool *open);

		static bool sortByFilename(const File &file1, const File &file2);

		static bool sortBySize(const File &file1, const File &file2);

		void sortDirectoryContent();

		void drawDialogHeader(float windowWidth, float windowHeight);

		void drawDialogBody(bool *open, float windowHeight, bool openAction);

		void buttonDoublePress();

		[[nodiscard]] bool directoryChosen() const;
	};
}

#endif //SURVIVE_FILECHOOSER_H
