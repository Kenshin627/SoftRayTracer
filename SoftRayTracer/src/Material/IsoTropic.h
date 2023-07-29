#pragma once
#include "Material.h"
#include "../Model/Hittable.h"

class IsoTropic :public Material 
{
public:
	IsoTropic(const glm::vec3& color);
	virtual bool Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter) override;
private:
	glm::vec3 albedo;
};