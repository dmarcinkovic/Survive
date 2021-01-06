//
// Created by david on 06. 12. 2020..
//

#ifndef SURVIVE_FILECHOOSER_H
#define SURVIVE_FILECHOOSER_H


#include <GL/glew.h>
#include <filesystem>
#include <string>
#include <vector>

struct File
{
	std::string name;
	unsigned long size = 0;
	std::filesystem::file_type type;
};

class FileChooser
{
private:
	static constexpr float TEXT_BASE_WIDTH = 10.0f;
	std::string m_CurrentDirectory;
	ImTextureID m_Icon{};
	int m_SelectedFile{};

	std::vector<File> m_DirectoryContent;
	bool m_Check{};
	bool m_Open;

	ImGuiStyle *m_Style;

public:
	FileChooser();

	void open(float windowWidth, float windowHeight);

private:
	void setupDarkStyleColors();

	static std::vector<File> listDirectory(const std::string &directory, bool showHidden = false);

	static std::vector<File> listCurrentDirectory(bool showHidden = false);

	static std::string getFileSize(unsigned long fileSize, std::filesystem::file_type type);

	static const char* getFileType(std::filesystem::file_type type);

	static void helpMarker(const char* description);

	static std::filesystem::path getParentPath(const std::string &currentDirectory);
};


#endif //SURVIVE_FILECHOOSER_H
