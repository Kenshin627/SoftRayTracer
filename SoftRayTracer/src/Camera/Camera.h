#pragma once
#include "../Renderer/Ray.h"
#include <glm/glm.hpp>

class Camera
{
public:
	Camera() = default;
	Camera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up, float aspect, float fovInDegree, float aperture);
	Ray EmitRay(float u, float v);
private:
	glm::vec3 z;
	glm::vec3 y;
	glm::vec3 x;
	glm::vec3 viewportWidth;
	glm::vec3 viewportHeight;
	float apertureRadius;
	float focalDistance;
	float fov;
	glm::vec3 position;
	glm::vec3 viewportOrigin;
};