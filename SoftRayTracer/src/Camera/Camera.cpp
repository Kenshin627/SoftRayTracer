#include "Camera.h"

Camera::Camera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up, float focalLength, float aspect, float height):focalLength(focalLength), position(eye)
{
	z = glm::normalize(eye - center);
	x = glm::normalize(glm::cross(up, z)) * aspect * height;
	y = glm::normalize(glm::cross(z,  x)) * height;
	viewportOrigin = -z * focalLength - x * 0.5f - y * 0.5f;
}

Ray Camera::EmitRay(float u, float v)
{
	return Ray(position, glm::normalize(viewportOrigin + u * x + v * y - position));
}