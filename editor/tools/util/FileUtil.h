//
// Created by david on 21. 08. 2021..
//

#ifndef SURVIVE_FILEUTIL_H
#define SURVIVE_FILEUTIL_H

#include <string>
#include <filesystem>
#include <vector>

namespace Survive
{
	struct File
	{
		std::filesystem::path path;
		unsigned long size = 0;
		std::filesystem::file_type type;
	};

	class FileUtil
	{
	public:
		static std::vector<File> listDirectory(const std::string &directory, bool showHidden = false);

		static std::vector<File> listCurrentDirectory();

		static std::string getFileSize(unsigned long fileSize, std::filesystem::file_type type);

		static const char *getFileType(std::filesystem::file_type type);
	};
}

#endif //SURVIVE_FILEUTIL_H
