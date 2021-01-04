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
	unsigned long size;
	std::filesystem::file_type type;
};

class FileChooser
{
public:
	static void open();

private:
	static std::vector<File> listDirectory(const std::string &directory);

	static std::vector<File> listCurrentDirectory();
};


#endif //SURVIVE_FILECHOOSER_H
