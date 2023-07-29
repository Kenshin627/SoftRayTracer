#include "IsoTropic.h"
#include "../utils/Utils.h"

IsoTropic::IsoTropic(const glm::vec3& color) :albedo(color) {}

bool IsoTropic::Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter)
{
	attenuation = albedo;
	scatter = Ray(rec.point, Tool::RandomInUnitSphere());
	return true;
}