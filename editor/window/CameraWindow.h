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
		static void draw(Camera &camera);

	private:
		static void setColors();

		static void drawHeader();

		static void drawCameraTransform(Camera &camera);

		static void drawCameraProperties(Camera &camera);

		static void drawClipPlanes(Camera &camera);

		static void showCameraProperties(Camera &camera);

		static float clampAngle(float angle);
	};
}

#endif //SURVIVE_CAMERAWINDOW_H
