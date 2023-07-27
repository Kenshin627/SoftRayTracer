#include "XYPlane.h"

XYPlane::XYPlane(float x0, float x1, float y0, float y1, float z, const std::shared_ptr<Material>& mat):Hittable(mat), xMin(x0), yMin(y0), xMax(x1), yMax(y1), z(z)
{
	
}

bool XYPlane::GetBoundingBox(BoundingBox& out)
{
	glm::vec3 min { xMin, yMin, z - 0.00001f };
	glm::vec3 max { xMax, yMax, z + 0.00001f };
	out = BoundingBox(min, max);
	return true;
}

bool XYPlane::Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec)
{
	float t = (z - ray.Origin().z) / ray.Direction().z;
	if (t < tMin || t > tMax)
	{
		return false;
	}
	float x = ray.Direction().x * t + ray.Origin().x;
	float y = ray.Direction().y * t + ray.Origin().y;
	bool isHit = x <= xMax && x >= xMin && y >= yMin && y <= yMax;
	if (!isHit)
	{
		return false;
	}
	rec.t = t;
	rec.material = material;
	glm::vec3 n = glm::vec3(0, 0, 1);
	rec.SetNormal(ray, n);
	return true;
}
