#pragma once
#include "Hittable.h"

class Sphere :public Hittable
{
public:
	Sphere(const glm::vec3& center, float radius, const std::shared_ptr<Material>& mat);
	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) override;
	virtual bool GetBoundingBox(BoundingBox& out) override;
private:
	glm::vec3 center;
	float radius;
};