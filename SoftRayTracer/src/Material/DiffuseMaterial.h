#pragma once
#include "Material.h"

class DiffuseMaterial :public Material
{
public:
	DiffuseMaterial(const glm::vec3& albedo);
	virtual bool Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter) override;
private:
	glm::vec3 albedo;
};