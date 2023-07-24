#pragma once
#include "Material.h"

class MetalMaterial :public Material
{
public:
	MetalMaterial(const glm::vec3& color, float roughness);
	virtual bool Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter) override;
private:
	glm::vec3 albedo;
	float roughness; //[0, 1]
};