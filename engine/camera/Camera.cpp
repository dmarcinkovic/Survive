//
// Created by david on 17. 05. 2020..
//

#include "Camera.h"

void Survive::Camera::invertPitch()
{
	pitch = -pitch;
}

void Survive::Camera::moveCameraInYDirection(float yDistance)
{
	position.y += yDistance;
}
