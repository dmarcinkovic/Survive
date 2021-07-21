//
// Created by david on 09. 05. 2021..
//

#ifndef SURVIVE_COMPONENTTEMPLATE_H
#define SURVIVE_COMPONENTTEMPLATE_H

#include <imgui.h>

#include "AudioMaster.h"
#include "ObjParser.h"
#include "Components.h"
#include "EditorUtil.h"
#include "FileChooser.h"
#include "Loader.h"

namespace Survive
{
	class ComponentTemplate
	{
	private:
		AudioMaster m_AudioMaster;
		FileChooser m_FileChooser;
		Loader m_Loader;

	public:
		template<typename ComponentType>
		void drawComponent(ComponentType &component, bool * = nullptr)
		{}
	};
}

#endif //SURVIVE_COMPONENTTEMPLATE_H
