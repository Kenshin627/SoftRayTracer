#include "Metal.h"
#include "../utils/Utils.h"

Metal::Metal(const glm::vec3& color, float roughness) :albedo(color), roughness(roughness) { }

bool Metal::Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter)
{
	attenuation = albedo;
	glm::vec3 reflectDir = Tool::Reflect(in.Direction(), rec.normal);
	scatter = Ray(rec.point, reflectDir + roughness * Tool::RandomInUnitSphere());
	return true;
}