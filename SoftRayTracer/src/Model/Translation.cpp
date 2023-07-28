#include "Translation.h"

Translation::Translation(const std::shared_ptr<Hittable>& target, const glm::vec3& offset) :target(target), offset(offset) {}

bool Translation::Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec)
{
	Ray offsetRay = Ray(ray.Origin() - offset, ray.Direction());
	if (target->Hit(offsetRay, tMin, tMax, rec))
	{
		rec.point = rec.point + offset;
		rec.SetNormal(offsetRay, rec.normal);
		return true;
	}
	return false;
}

bool Translation::GetBoundingBox(BoundingBox& out)
{
	if (!target->GetBoundingBox(out))
	{
		return false;
	}
	out = BoundingBox(out.Min() + offset, out.Max() + offset);
	return true;
}