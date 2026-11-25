#include "IsoTropic.h"
#include "../Renderer/Sampling.h"

IsoTropic::IsoTropic(const glm::vec3& color) :IsoTropic(std::make_shared<SolidColor>(color)) {}

bool IsoTropic::Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter)
{
	attenuation = albedo->Value(rec.uv, rec.point);
	scatter = Ray(rec.point, Tool::RandomInUnitSphere(), in.Time());
	return true;
}
float IsoTropic::ScatteringPdf(const HitRecord&, const Ray&) const
{
	return 1.0f / (4 * Sampling::Pi);
}
