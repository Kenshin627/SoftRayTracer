#include "XZPlane.h"

XZPlane::XZPlane(float x0, float x1, float z0, float z1, float y, const std::shared_ptr<Material>& mat) :Hittable(mat), xMin(x0), zMin(z0), xMax(x1), zMax(z1), y(y)
{

}

bool XZPlane::GetBoundingBox(BoundingBox& out)
{
	glm::vec3 min { xMin, zMin, y - 0.00001f };
	glm::vec3 max { xMax, zMax, y + 0.00001f };
	out = BoundingBox(min, max);
	return true;
}

bool XZPlane::Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec)
{
	float t = (y - ray.Origin().y) / ray.Direction().y;
	if (t < tMin || t > tMax)
	{
		return false;
	}
	float x = ray.Direction().x * t + ray.Origin().x;
	float z = ray.Direction().z * t + ray.Origin().z;
	bool isHit = x <= xMax && x >= xMin && z >= zMin && z <= zMax;
	if (!isHit)
	{
		return false;
	}
	rec.t = t;
	rec.material = material;
	glm::vec3 n = glm::vec3(0, 1, 0);
	rec.SetNormal(ray, n);
	return true;
}
