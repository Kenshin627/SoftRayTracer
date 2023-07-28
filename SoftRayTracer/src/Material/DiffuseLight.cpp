#include "DiffuseLight.h"

DiffuseLight::DiffuseLight(const glm::vec3& color) :emit(color) {}

bool DiffuseLight::Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter)
{
	return false;
}

glm::vec3 DiffuseLight::Emitter(float u, float v, const glm::vec3& p)
{
	return emit;
}