#include "Camera.h"
#include "../utils/Utils.h"
Camera::Camera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up, float aspect, float fovInDegree, float aperture, float focalDis): position(eye), fov(glm::radians(fovInDegree)), apertureRadius(aperture / 2.0f), focalDistance(focalDis)
{
	float h = glm::tan(fov / 2.0f) * focalDistance;
	float height = h * 2.0f;
	float width = aspect * height;
	z = glm::normalize(eye - center);
	x = glm::normalize(glm::cross(up, z));
	y = glm::normalize(glm::cross(z,  x));
	horizontal = x * width;
	vertical = y * height;

	viewportOrigin = position - z * focalDistance - horizontal * 0.5f - vertical * 0.5f; //leftbottom
}

Ray Camera::EmitRay(float u, float v)
{
	glm::vec3 offset = apertureRadius * Tool::RandomInUnitDesk();
	glm::vec3 originPos = position + offset.x * x + offset.y * y;
	return Ray(originPos, viewportOrigin + u * horizontal + v * vertical - originPos);
}