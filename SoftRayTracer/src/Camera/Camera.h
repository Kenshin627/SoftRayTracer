#pragma once
#include "../Renderer/Ray.h"
#include <glm/glm.hpp>

class Camera
{
public:
	Camera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up, float focalLength, float aspect, float height);
	Ray EmitRay(float u, float v);
private:
	glm::vec3 z;
	glm::vec3 y;
	glm::vec3 x;
	float focalLength;
	glm::vec3 position;
};