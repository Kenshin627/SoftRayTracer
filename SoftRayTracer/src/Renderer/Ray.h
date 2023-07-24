#pragma once
#include <glm/glm.hpp>

class Ray
{
public:
	Ray() = default;
	Ray(const glm::vec3& origin, const glm::vec3& direction);
	const glm::vec3& Origin() const { return origin; }
	const glm::vec3& Direction() const { return direction; }
	glm::vec3 At(float t) const;
private:
	glm::vec3 origin;
	glm::vec3 direction;
};