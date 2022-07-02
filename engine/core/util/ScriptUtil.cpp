//
// Created by david on 28.06.22..
//

#include <sstream>
#include <fstream>

#include "ScriptUtil.h"
#include "FileUtil.h"
#include "Log.h"

std::string
Survive::ScriptUtil::compileScript(const std::filesystem::path &path, const std::filesystem::path &destination,
								   const std::filesystem::path &libraryLocation,
								   const std::filesystem::path &includeDirectory)
{
	static const std::string buildDirectoryName = "SurviveScriptBuild";
	std::string projectName = path.filename();

	const std::string cmakeFileContent = getCmakeFileContent(projectName, libraryLocation, includeDirectory, path);
	writeCmakeFile(destination, cmakeFileContent);

	std::filesystem::path buildDirectory(destination / buildDirectoryName);
	if (!std::filesystem::exists(buildDirectory))
	{
		std::filesystem::create_directory(buildDirectory);
	}

	std::string scriptPath;
	if (!executeCmakeCommand(destination, buildDirectory, projectName, scriptPath))
	{
		Log::logMessage(LogType::ERROR, "Error while compiling script");
		return "";
	}

	Log::logMessage(LogType::INFO, "Successfully compiled script");
	return scriptPath;
}

std::string
Survive::ScriptUtil::getCmakeFileContent(const std::string &projectName, const std::filesystem::path &libraryLocation,
										 const std::filesystem::path &includeDirectory,
										 const std::filesystem::path &scriptPath)
{
	std::stringstream ss;

	ss << "cmake_minimum_required(VERSION 3.22)\n";
	ss << "project(" << projectName << ")\n";
	ss << "set(CMAKE_CXX_STANDARD 20)\n";
	ss << "find_package(box2d REQUIRED)\n";
	ss << "find_library(SURVIVE_LIBRARY NAMES Survive HINTS " << absolute(libraryLocation).string() << ")\n";
	ss << "add_library(" << projectName << " SHARED " << absolute(scriptPath).string() << ")\n";
	ss << "target_include_directories(" << projectName << " PRIVATE " << absolute(includeDirectory).string() << ")\n";
	ss << "target_link_libraries(" << projectName << " PRIVATE box2d ${SURVIVE_LIBRARY})\n";

	return ss.str();
}

void Survive::ScriptUtil::writeCmakeFile(const std::filesystem::path &destination, const std::string &cmakeFileContent)
{
	const std::filesystem::path cmakePath(destination / "CMakeLists.txt");
	std::ofstream writer(cmakePath.string());

	writer << cmakeFileContent;
	writer.flush();

	writer.close();
}

bool Survive::ScriptUtil::executeCmakeCommand(const std::filesystem::path &destination,
											  const std::filesystem::path &buildDirectory,
											  const std::string &projectName, std::string &scriptPath)
{
	const std::string command = getCmakeCommand(destination, buildDirectory);
	std::system(command.c_str());

	std::vector<File> content = FileUtil::listDirectory(absolute(buildDirectory).string());
	for (auto const &file: content)
	{
		if (file.path.filename().string().find(projectName) != std::string::npos)
		{
			scriptPath = absolute(file.path).string();
			return true;
		}
	}

	return false;
}

std::string
Survive::ScriptUtil::getCmakeCommand(const std::filesystem::path &destination,
									 const std::filesystem::path &buildDirectory)
{
	std::stringstream ss;
	ss << "cd " << destination.string() << " && cmake . -B " << buildDirectory.string() << " && cd "
	   << buildDirectory.string() << " && cmake --build . --config Release";

	return ss.str();
}
