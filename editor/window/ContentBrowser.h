//
// Created by david on 18. 08. 2021..
//

#ifndef SURVIVE_CONTENTBROWSER_H
#define SURVIVE_CONTENTBROWSER_H

#include <imgui.h>
#include <vector>
#include <stack>

#include "FileUtil.h"
#include "Texture.h"
#include "DirectoryTree.h"
#include "Loader.h"

namespace Survive
{
	enum Files
	{
		FOLDER, TXT, CPP, README, IMAGE, OBJ, UNKNOWN, SURVIVE, DAE
	};

	class ContentBrowser
	{
	private:
		static constexpr float ICON_SIZE = 70.0f;
		static constexpr float SPACING = 30.0f;
		static constexpr float TEXT_WIDTH = 70.0f;
		static constexpr float COLUMN_WIDTH = 250.0f;

		static constexpr size_t BUFFER_SIZE = 256;

		Loader m_Loader;

		const ImVec2 m_Uv0, m_Uv1;
		std::vector<File> m_DirectoryContent;

		Texture m_Lupa;
		int m_ImageIndex{};

		char m_Buffer[BUFFER_SIZE]{};
		std::vector<Texture> m_Icons;

		std::filesystem::path m_CurrentDirectory;
		std::filesystem::path m_DraggedFile;
		DirectoryTree m_Tree;

		std::string m_ImageFilename;

		bool m_DrawImage{};
		Texture m_Image{};

		bool m_WidthSet{};
		bool m_ContentChanged{};
		bool m_StartedDragging{};

		bool m_InputText{};

	public:
		ContentBrowser();

		void draw();

		[[nodiscard]] bool startedDragging() const;

		void stopDragging();

		[[nodiscard]] const std::filesystem::path &getDraggedFile() const;

		[[nodiscard]] bool isUsingKeyEvents() const;

	private:
		static void setColors();

		[[nodiscard]] ImTextureID getIcon(const std::filesystem::path &file);

		void drawIcon(ImTextureID image, const std::filesystem::path &file);

		static void alignIcons(float availableRegion);

		void drawDirectoryContent();

		void renderImageWindow();

		void drawTextDialog();

		void startDraggingIcon(const std::filesystem::path &file);

		void iconDoubleClicked(const std::filesystem::path &file);
	};
}

#endif //SURVIVE_CONTENTBROWSER_H
