#include "DiffuseMaterial.h"
#include "../utils/Utils.h"

DiffuseMaterial::DiffuseMaterial(const glm::vec3& color) :albedo(color) {}

bool DiffuseMaterial::Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter)
{
	attenuation = albedo;
	glm::vec3 reflectDir = rec.normal + Tool::RandomInUnitSphere();
	if (Tool::NearZero(reflectDir))
	{
		reflectDir = rec.normal;
	}
	scatter = Ray(rec.point, reflectDir);
	return true;
}