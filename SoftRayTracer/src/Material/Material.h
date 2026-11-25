#pragma once
#include "../Renderer/Ray.h"

struct HitRecord;
class Material
{
public:
	Material();
	virtual ~Material() = default;
	virtual bool Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter) = 0;
	virtual bool HasScatteringPdf() const { return false; }
	virtual float ScatteringPdf(const HitRecord&, const Ray&) const { return 0; }
	virtual glm::vec3 Emitter(const HitRecord& rec);
};