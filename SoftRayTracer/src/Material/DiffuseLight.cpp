#include "DiffuseLight.h"
#include "../Model/Hittable.h"

DiffuseLight::DiffuseLight(const glm::vec3& color) :DiffuseLight(std::make_shared<SolidColor>(color)) {}

bool DiffuseLight::Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter)
{
	return false;
}

glm::vec3 DiffuseLight::Emitter(const HitRecord& rec)
{
	return rec.frontFace ? emit->Value(rec.uv, rec.point) : glm::vec3(0);
}