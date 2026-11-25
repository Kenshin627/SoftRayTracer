#include "Material.h"
#include "../Model/Hittable.h"

Material::Material() {}

glm::vec3 Material::Emitter(const HitRecord&)
{
	return glm::vec3(0, 0, 0);
}