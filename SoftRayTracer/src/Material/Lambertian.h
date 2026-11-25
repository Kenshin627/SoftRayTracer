#pragma once
#include "Material.h"
#include "Texture.h"
#include "../Model/Hittable.h"

class Lambertian :public Material
{
public:
	Lambertian(const glm::vec3& albedo);
	explicit Lambertian(std::shared_ptr<Texture> texture) : albedo(texture) {}
	virtual bool Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter) override;
bool HasScatteringPdf() const override { return true; }
	float ScatteringPdf(const HitRecord& rec, const Ray& ray) const override;
private:
	std::shared_ptr<Texture> albedo;
};