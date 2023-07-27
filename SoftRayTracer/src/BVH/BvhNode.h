#pragma once
#include "../Model/HittableList.h"
#include <memory>

class BvhNode :public Hittable
{
public:
	BvhNode(const HittableList& list);
	BvhNode(const std::vector <std::shared_ptr<Hittable>>& objects, uint32_t start, uint32_t end);
	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) override;
	virtual bool GetBoundingBox(BoundingBox& out) override;
private:
	std::shared_ptr<Hittable> left;
	std::shared_ptr<Hittable> right;
	BoundingBox aabb;
};