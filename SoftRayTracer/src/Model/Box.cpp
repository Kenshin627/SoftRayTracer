#include "Box.h"

Box::Box(const glm::vec3& center, uint32_t width, uint32_t height, uint32_t depth, const std::shared_ptr<Material>& mat) :Hittable(mat)
{
	glm::vec3 min = center - glm::vec3(width, height, depth);
	glm::vec3 max = center + glm::vec3(width, height, depth);
	aabb = BoundingBox(min, max);
	//planes
}

bool Box::Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec)
{
	return planes.Hit(ray, tMin, tMax, rec);
}