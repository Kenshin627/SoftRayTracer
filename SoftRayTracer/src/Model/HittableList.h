#pragma once
#include "Hittable.h"
#include <vector>
#include <memory>

class HittableList :public Hittable 
{
public:
	HittableList() = default;
	void AddObject(const std::shared_ptr<Hittable>& obj);
	const std::vector<std::shared_ptr<Hittable>>& GetAll() const { return objects; }
	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) override;
	virtual bool GetBoundingBox(BoundingBox& out) override;
private:
	std::vector<std::shared_ptr<Hittable>> objects;
};