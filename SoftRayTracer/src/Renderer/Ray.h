#pragma once
#include <glm/glm.hpp>

class Ray
{
public:
	Ray() = default;
	Ray(const glm::vec3& origin, const glm::vec3& direction, float time = 0);
	float Time() const { return time; }
	const glm::vec3& Origin() const { return origin; }
	const glm::vec3& Direction() const { return direction; }
	glm::vec3 At(float t) const;
private:
	float time = 0;
	glm::vec3 origin;
	glm::vec3 direction;
};