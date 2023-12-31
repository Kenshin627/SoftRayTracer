#pragma once
#include "XYPlane.h"
#include "XZPlane.h"
#include "YZPlane.h"
#include "HittableList.h"

class Box :public Hittable
{
public:
	Box(const glm::vec3& center, uint32_t width, uint32_t height, uint32_t depth, const std::shared_ptr<Material>& mat);
	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) override;
	virtual bool GetBoundingBox(BoundingBox& out) override;
private:
	HittableList faces;
	BoundingBox aabb;
};