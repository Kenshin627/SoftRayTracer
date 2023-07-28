#include "Material.h"
#include "../Model/Hittable.h"

Material::Material() {}

glm::vec3 Material::Emitter(float u, float v, const glm::vec3& p)
{
	return glm::vec3(0, 0, 0);
}