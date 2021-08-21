//
// Created by david on 18. 08. 2021..
//

#include <filesystem>
#include <iostream>

#include "ContentBrowser.h"

Survive::ContentBrowser::ContentBrowser()
{
	auto workingDirectory = std::filesystem::current_path();
	std::cout << workingDirectory << '\n';
}

void Survive::ContentBrowser::draw()
{
	if (ImGui::Begin("Content browser"))
	{
		ImGui::End();
	}
}
