#include "Lambertian.h"
#include "../Renderer/Sampling.h"

Lambertian::Lambertian(const glm::vec3& color) :Lambertian(std::make_shared<SolidColor>(color)) {}

bool Lambertian::Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter)
{
	attenuation = albedo->Value(rec.uv, rec.point);
	scatter = Ray(rec.point, Sampling::CosineHemisphere(rec.normal), in.Time());
	return true;
}

float Lambertian::ScatteringPdf(const HitRecord& rec, const Ray& ray) const
{
	return glm::max(0.0f, glm::dot(rec.normal, ray.Direction())) / Sampling::Pi;
}
