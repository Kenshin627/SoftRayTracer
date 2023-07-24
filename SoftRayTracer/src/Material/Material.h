#pragma once
#include "../Model/Hittable.h"
#include "../Renderer/Ray.h"

class Material
{
public:
	Material() = default;
	virtual ~Material() = default;
	virtual bool Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter) = 0;
};