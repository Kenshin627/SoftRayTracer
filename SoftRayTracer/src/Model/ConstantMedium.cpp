#include "ConstantMedium.h"
#include "../Material/IsoTropic.h"
#include "../utils/Utils.h"
#include <memory>

ConstantMedium::ConstantMedium(std::shared_ptr<Hittable> target, float density, const glm::vec3& color) :boundary(target), parseFunction(std::make_shared<IsoTropic>(color)), negInvDensity(-1.0f / density) { }

bool ConstantMedium::Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec)
{
	HitRecord rec1, rec2;
	constexpr auto infinity = std::numeric_limits<float>::infinity();

	if (!boundary->Hit(ray, -infinity, infinity, rec1))
	{
		return false;
	}

	if (!boundary->Hit(ray, rec1.t + 0.0001, infinity, rec2))
	{
		return false;
	}
	if (rec1.t < tMin)
	{
		rec1.t = tMin;
	}

	if (rec2.t > tMax)
	{
		rec2.t = tMax;
	}
	const auto rayLen = glm::length(ray.Direction());
	const auto distanceInsideBoundary = (rec2.t - rec1.t) * rayLen;
	const auto hitDistance = negInvDensity * glm::log(Tool::Random());
	if (hitDistance > distanceInsideBoundary)
	{
		return false;
	}
	rec.t = rec1.t + hitDistance / rayLen;
	rec.point = ray.At(rec.t);
	rec.normal = glm::vec3(1.0f, 0.0f, 0.0f); 
	rec.frontFace = true;
	rec.material = parseFunction;

	return true;
}

bool ConstantMedium::GetBoundingBox(BoundingBox& out)
{
	return boundary->GetBoundingBox(out);
}