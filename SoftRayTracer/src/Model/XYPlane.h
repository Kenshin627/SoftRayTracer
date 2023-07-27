#pragma once
#include "Hittable.h"

class XYPlane :public Hittable
{
public:
	XYPlane(float x0, float x1, float y0, float y1, float z, const std::shared_ptr<Material>& mat);
	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) override;
	virtual bool GetBoundingBox(BoundingBox& out) override;
private:
	float xMin;
	float xMax;
	float yMin;
	float yMax;
	float z;
};