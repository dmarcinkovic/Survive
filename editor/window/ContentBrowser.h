//
// Created by david on 18. 08. 2021..
//

#ifndef SURVIVE_CONTENTBROWSER_H
#define SURVIVE_CONTENTBROWSER_H

#include <imgui.h>
#include <vector>

#include "FileUtil.h"
#include "Texture.h"

namespace Survive
{
	enum Files
	{
		FOLDER, BINARY, TXT, CPP, README, IMAGE, OBJ, UNKNOWN
	};

	class ContentBrowser
	{
	private:
		static constexpr float ICON_SIZE = 70.0f;
		static constexpr float SPACING = 30.0f;
		static constexpr float TEXT_WIDTH = 70.0f;
		static constexpr float COLUMN_WIDTH = 250.0f;

		const ImVec2 m_Uv0, m_Uv1;
		std::vector<File> m_DirectoryContent{};
		std::vector<std::vector<File>> m_NestedDirectories{};

		int m_ImageIndex{};

		std::vector<Texture> m_Icons;
		std::filesystem::path m_CurrentDirectory;
		std::filesystem::path m_ShowingDirectory;

		bool m_DrawImage{};
		Texture m_Image{};

		bool m_WidthSet{};

	public:
		ContentBrowser();

		void draw();

	private:
		static void setColors();

		[[nodiscard]] ImTextureID getIcon(const std::filesystem::path &file);

		void drawIcon(ImTextureID image, const std::filesystem::path &file);

		static void alignIcons(float availableRegion);

		void drawDirectoryContent();

		void drawDirectoryTree();

		static void setDirectoryTreeColors();

		void drawTree();

		void renderImageWindow();
	};
}

#endif //SURVIVE_CONTENTBROWSER_H
