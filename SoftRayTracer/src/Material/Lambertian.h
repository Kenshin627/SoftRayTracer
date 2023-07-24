#pragma once
#include "Material.h"
#include "../Model/Hittable.h"

class Lambertian :public Material
{
public:
	Lambertian(const glm::vec3& albedo);
	virtual bool Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter) override;
private:
	glm::vec3 albedo;
};