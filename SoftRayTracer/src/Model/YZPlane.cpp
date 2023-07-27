#include "YZPlane.h"

YZPlane::YZPlane(float y0, float y1, float z0, float z1, float x, const std::shared_ptr<Material>& mat) :Hittable(mat), yMin(y0), zMin(z0), yMax(y1), zMax(z1), x(x)
{

}

bool YZPlane::GetBoundingBox(BoundingBox& out)
{
	glm::vec3 min { yMin, zMin, x - 0.00001f };
	glm::vec3 max { yMax, zMax, x + 0.00001f };
	out = BoundingBox(min, max);
	return true;
}

bool YZPlane::Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec)
{
	float t = (x - ray.Origin().x) / ray.Direction().x;
	if (t < tMin || t > tMax)
	{
		return false;
	}
	float y = ray.Direction().y * t + ray.Origin().y;
	float z = ray.Direction().z * t + ray.Origin().z;
	bool isHit = y <= yMax && y >= yMin && z >= zMin && z <= zMax;
	if (!isHit)
	{
		return false;
	}
	rec.t = t;
	rec.material = material;
	glm::vec3 n = glm::vec3(1, 0, 0);
	rec.SetNormal(ray, n);
	return true;
}
