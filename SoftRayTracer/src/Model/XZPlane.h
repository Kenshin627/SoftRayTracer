#pragma once
#include "Hittable.h"

class XZPlane :public Hittable
{
public:
	XZPlane(float x0, float x1, float z0, float z1, float y, const std::shared_ptr<Material>& mat);
	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) override;
	virtual bool GetBoundingBox(BoundingBox& out) override;
private:
	float xMin;
	float xMax;
	float zMin;
	float zMax;
	float y;
};