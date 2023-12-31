#include "XZPlane.h"

XZPlane::XZPlane(float x0, float x1, float z0, float z1, float y, const std::shared_ptr<Material>& mat) :Hittable(mat), xMin(x0), zMin(z0), xMax(x1), zMax(z1), y(y) {}

bool XZPlane::GetBoundingBox(BoundingBox& out)
{
	glm::vec3 min { xMin, y - 0.0001f, zMin };
	glm::vec3 max { xMax, y + 0.0001f, zMax };
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
	if (x > xMax || x < xMin || z > zMax || z < zMin)
	{
		return false;
	}
	rec.t = t;
	rec.point = ray.At(t);
	rec.material = material;
	glm::vec3 n = glm::vec3(0, 1, 0);
	rec.SetNormal(ray, n);
	return true;
}
