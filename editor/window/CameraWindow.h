//
// Created by david on 07. 10. 2021..
//

#ifndef SURVIVE_CAMERAWINDOW_H
#define SURVIVE_CAMERAWINDOW_H

#include <imgui.h>

#include "Camera.h"

namespace Survive
{
	class CameraWindow
	{
	public:
		void draw(const Camera  &camera);
	};
}

#endif //SURVIVE_CAMERAWINDOW_H
