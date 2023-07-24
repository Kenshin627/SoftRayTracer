#include "Dielectric.h"
#include "../utils/Utils.h"
bool Dielectric::Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter)
{
	attenuation = { 1.0f, 1.0f ,1.0f };
	float refractionRatio = rec.frontFace ? 1.0f / ior : ior / 1.0f;
	float cosTheta = glm::dot(-in.Direction(), rec.normal);
	float sinTheta = glm::sqrt(1.0f - cosTheta * cosTheta);
	bool canNotRefract = refractionRatio * sinTheta > 1.0f;
	if (canNotRefract || SchlickFernelApprox(cosTheta, refractionRatio))
	{
		glm::vec3 refract = Tool::Reflact(in.Direction(), rec.normal, refractionRatio);
		scatter = Ray(rec.point, refract);
	}
	else
	{
		glm::vec3 refect = Tool::Reflect(in.Direction(), rec.normal);
	}
	return true;
}

float Dielectric::SchlickFernelApprox(float cosTheta, float refractionRatio)
{
	float F0 = (1.0f - refractionRatio) / (1.0f + refractionRatio);
	F0 = F0 * F0;
	return F0 + (1.0f - F0) * glm::pow((1.0f - cosTheta), 5.0f);
}