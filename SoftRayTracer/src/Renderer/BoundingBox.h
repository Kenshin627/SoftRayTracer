#pragma once
#include "Ray.h"
#include <glm/glm.hpp>

enum Axis
{
	x = 0,
	y,
	z
};

class BoundingBox
{
public:
	BoundingBox() = default;
	BoundingBox(const glm::vec3& min, const glm::vec3& max);
	BoundingBox(const BoundingBox& box1, const BoundingBox& box2);
	static BoundingBox SurroundingBox(const BoundingBox& box1, const BoundingBox& box2);
	bool Hit(const Ray& ray, float minTime, float maxTime);
	const glm::vec3& Min() const { return min; }
	const glm::vec3& Max() const { return max; }
	Axis LongestAxis();
private:
	glm::vec3 min;
	glm::vec3 max;
};