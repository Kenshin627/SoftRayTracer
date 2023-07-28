#pragma once
#include "../Renderer/Ray.h"

struct HitRecord;
class Material
{
public:
	Material();
	virtual ~Material() = default;
	virtual bool Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter) = 0;
	virtual glm::vec3 Emitter(float u, float v, const glm::vec3& p);
};