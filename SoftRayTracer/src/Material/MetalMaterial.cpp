#include "MetalMaterial.h"

MetalMaterial::MetalMaterial(const glm::vec3& color, float roughness):albedo(color), roughness(roughness)
{

}

bool MetalMaterial::Scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scatter)
{
	
}