//
// Created by david on 28.06.22..
//

#ifndef SURVIVE_SCRIPTUTIL_H
#define SURVIVE_SCRIPTUTIL_H

#include <string>
#include <filesystem>

namespace Survive
{
	class ScriptUtil
	{
	public:
		static std::string compileScript(const std::filesystem::path &path, const std::filesystem::path &destination,
										 const std::filesystem::path &libraryLocation,
										 const std::filesystem::path &includeDirectory);

	private:
		static std::string
		getCmakeFileContent(const std::string &projectName, const std::filesystem::path &libraryLocation,
							const std::filesystem::path &includeDirectory, const std::filesystem::path &scriptPath);

		static void writeCmakeFile(const std::filesystem::path &destination, const std::string &cmakeFileContent);

		static bool
		executeCmakeCommand(const std::filesystem::path &destination, const std::filesystem::path &buildDirectory,
							const std::string &projectName, std::string &scriptPath);

		static std::string
		getCmakeCommand(const std::filesystem::path &destination, const std::filesystem::path &buildDirectory);
	};
}


#endif //SURVIVE_SCRIPTUTIL_H
