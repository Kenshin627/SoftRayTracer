#pragma once
#include "Material.h"
#include "Texture.h"

class DiffuseLight :public Material
{
public:
	DiffuseLight(const glm::vec3& color);
	explicit DiffuseLight(std::shared_ptr<Texture> texture) : emit(texture) {}
	virtual bool Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter) override;
	virtual glm::vec3 Emitter(const HitRecord& rec) override;
private:
	std::shared_ptr<Texture> emit;
};