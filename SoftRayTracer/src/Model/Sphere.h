#pragma once
#include "Hittable.h"

class Sphere :public Hittable
{
public:
	Sphere(const glm::vec3& center, float radius);
	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) override;
private:
	glm::vec3 center;
	float radius;
};