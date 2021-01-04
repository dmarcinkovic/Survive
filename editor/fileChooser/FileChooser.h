//
// Created by david on 06. 12. 2020..
//

#ifndef SURVIVE_FILECHOOSER_H
#define SURVIVE_FILECHOOSER_H


#include <GL/glew.h>
#include <string>
#include <vector>

class FileChooser
{
public:
	static void open();

public:
	static std::vector<std::string> listDirectory(const std::string &directory);

	static std::vector<std::string> listCurrentDirectory();
};


#endif //SURVIVE_FILECHOOSER_H
