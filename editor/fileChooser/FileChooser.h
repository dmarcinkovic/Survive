//
// Created by david on 06. 12. 2020..
//

#ifndef SURVIVE_FILECHOOSER_H
#define SURVIVE_FILECHOOSER_H


#include <filesystem>
#include <string>
#include <vector>
#include <stack>

struct File
{
	std::string name;
	unsigned long size = 0;
	std::filesystem::file_type type;
};

class FileChooser
{
private:
	static constexpr ImGuiTableFlags tableFlags =
			ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_Sortable |
			ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_Reorderable | ImGuiTableFlags_ScrollY;

	std::string m_CurrentDirectory;
	const std::filesystem::path m_Root;

	ImTextureID m_Icon{};
	int m_SelectedFile{};

	std::vector<File> m_DirectoryContent;
	bool m_Hidden{};
	bool m_Previous{};

	ImGuiStyle *m_Style;

	std::string m_SelectedFileName;
	std::stack<std::string> m_Undo;
	std::stack<std::string> m_Redo;

public:
	FileChooser();

	void open(float windowWidth, float windowHeight, bool *open);

private:
	void setupDarkStyleColors();

	void drawNavigationArrows();

	void drawLeftArrow();

	void drawRightArrow();

	void drawUpArrow();

	void drawCheckbox();

	void drawFilenameTextbox(bool *open);

	void drawTable(float windowHeight, bool *open);

	void drawHeader();

	void drawOpenButton(bool *open);

	void drawCancelButton(bool *open);

	static std::vector<File> listDirectory(const std::string &directory, bool showHidden = false);

	static std::vector<File> listCurrentDirectory(bool showHidden = false);

	static std::string getFileSize(unsigned long fileSize, std::filesystem::file_type type);

	static const char *getFileType(std::filesystem::file_type type);

	static void helpMarker(const char *description);

	static std::filesystem::path getParentPath(const std::string &currentDirectory);

	[[nodiscard]] std::string getSelectedFile() const;

	void resetSelectedFile();

	void drawIcon();

	void fillTableRow(const File &file, int index, bool *open);

	void openPressed(bool *open);

	static bool sortByFilename(const File &file1, const File &file2);

	static bool sortBySize(const File &file1, const File &file2);

	void sortDirectoryContent();
};


#endif //SURVIVE_FILECHOOSER_H
