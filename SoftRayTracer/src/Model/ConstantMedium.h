#pragma once
#include "Hittable.h"

class ConstantMedium :public Hittable
{
public:
	ConstantMedium(std::shared_ptr<Hittable> target, float density, const glm::vec3& color);
	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) override;
	virtual bool GetBoundingBox(BoundingBox& out) override;
private:
	std::shared_ptr<Hittable> boundary;
	std::shared_ptr<Material> parseFunction;
	float negInvDensity;
};