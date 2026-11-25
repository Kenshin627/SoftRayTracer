#include "ConstantMedium.h"
#include "../Material/IsoTropic.h"
#include "../utils/Utils.h"
#include <memory>
#include <stdexcept>

ConstantMedium::ConstantMedium(std::shared_ptr<Hittable> target, float density, const glm::vec3& color) : ConstantMedium(target, density, std::make_shared<SolidColor>(color)) {}

ConstantMedium::ConstantMedium(std::shared_ptr<Hittable> target, float density, std::shared_ptr<Texture> texture)
    : boundary(target), parseFunction(std::make_shared<IsoTropic>(texture)), negInvDensity(-1.0f / density)
{
    if (density <= 0) throw std::invalid_argument("medium density must be positive");
}

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
	rec.uv = glm::vec2(0);
	rec.material = parseFunction;

	return true;
}

bool ConstantMedium::GetBoundingBox(BoundingBox& out)
{
	return boundary->GetBoundingBox(out);
}