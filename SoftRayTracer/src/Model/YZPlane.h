#pragma once
#include "Hittable.h"

class YZPlane :public Hittable
{
public:
	YZPlane(float y0, float y1, float z0, float z1, float x, const std::shared_ptr<Material>& mat);
	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) override;
	virtual bool GetBoundingBox(BoundingBox& out) override;
private:
	float yMin;
	float yMax;
	float zMin;
	float zMax;
	float x;
};