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
public:
	static void open(GLuint icon);

private:
	static std::vector<File> listDirectory(const std::string &directory);

	static std::vector<File> listCurrentDirectory();

	static std::string getFileSize(unsigned long fileSize, std::filesystem::file_type type);

	static const char* getFileType(std::filesystem::file_type type);
};


#endif //SURVIVE_FILECHOOSER_H
