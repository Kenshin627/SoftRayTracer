#pragma once
#include "Hittable.h"

class Translation :public Hittable
{
public:
	Translation(const std::shared_ptr<Hittable>& target, const glm::vec3& offset);
	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) override;
	virtual bool GetBoundingBox(BoundingBox& out) override;
private:
	std::shared_ptr<Hittable> target;
	glm::vec3 offset;
};