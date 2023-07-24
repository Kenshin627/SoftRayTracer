#pragma once
#include "Material.h"
#include "../Model/Hittable.h"

class Dielectric :public Material
{
public:
	Dielectric(float ior) :ior(ior) {}
	virtual bool Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter) override;
	float SchlickFernelApprox(float cosTheta, float refractionRatio);
private:
	float ior;
};