//
// Created by david on 21. 08. 2021..
//

#include "FileUtil.h"


std::vector<Survive::File> Survive::FileUtil::listCurrentDirectory()
{
	auto workingDirectory = std::filesystem::current_path();

	return listDirectory(std::filesystem::absolute(workingDirectory).string(), false);
}

std::vector<Survive::File> Survive::FileUtil::listDirectory(const std::string &directory, bool showHidden)
{
	std::filesystem::directory_iterator directoryIterator(directory);
	std::vector<File> files;

	for (auto const &path : directoryIterator)
	{
		File file;
		file.path = path.path();
		std::string filename = file.path.filename().string();

		if (!showHidden && filename.front() == '.')
		{
			continue;
		}

		if (path.is_regular_file())
		{
			file.size = path.file_size();
		}

		file.type = path.status().type();
		files.emplace_back(file);
	}

	return files;
}

std::string Survive::FileUtil::getFileSize(unsigned long fileSize, std::filesystem::file_type type)
{
	if (type != std::filesystem::file_type::regular)
	{
		return "";
	}

	static const int BYTE = 1024;
	auto size = static_cast<double>(fileSize);

	double kilobytes = size / BYTE;

	if (kilobytes < 1.0)
	{
		return std::to_string(fileSize);
	}

	std::ostringstream stream;

	double megabytes = kilobytes / BYTE;

	if (megabytes < 1.0)
	{
		stream << std::setprecision(3) << kilobytes << "K";
		return stream.str();
	}

	double gigabytes = megabytes / BYTE;

	if (gigabytes < 1.0)
	{
		stream << std::setprecision(3) << megabytes << "M";
		return stream.str();
	}

	double terabytes = gigabytes / BYTE;

	if (terabytes < 1.0)
	{
		stream << std::setprecision(3) << gigabytes << "G";
		return stream.str();
	}

	stream << std::setprecision(3) << terabytes << "T";
	return stream.str();
}

const char *Survive::FileUtil::getFileType(std::filesystem::file_type type)
{
	switch (type)
	{
		case std::filesystem::file_type::directory :
			return "directory";
		case std::filesystem::file_type::none:
			return "none";
		case std::filesystem::file_type::not_found:
			return "not found";
		case std::filesystem::file_type::regular:
			return "regular";
		case std::filesystem::file_type::symlink:
			return "symlink";
		case std::filesystem::file_type::block:
			return "block";
		case std::filesystem::file_type::character:
			return "character";
		case std::filesystem::file_type::fifo:
			return "fifo";
		case std::filesystem::file_type::socket:
			return "socket";
		case std::filesystem::file_type::unknown:
			return "unknown";
		default:
			return "";
	}
}
