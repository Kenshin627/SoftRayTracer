#pragma once
#include "../Renderer/Ray.h"

struct HitRecord;
class Material
{
public:
	Material();
	virtual ~Material() = default;
	virtual bool Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter) = 0;
};