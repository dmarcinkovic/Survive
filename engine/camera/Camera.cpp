//
// Created by david on 17. 05. 2020..
//

#include "Camera.h"

void Camera::invertPitch()
{
	pitch = -pitch;
}

void Camera::moveCameraInYDirection(float yDistance)
{
	position.y += yDistance;
}
