#pragma once
#include "Material.h"

class DiffuseLight :public Material
{
public:
	DiffuseLight(const glm::vec3& color);
	virtual bool Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter) override;
	virtual glm::vec3 Emitter(float u, float v, const glm::vec3& p) override;
private:
	glm::vec3 emit;
};