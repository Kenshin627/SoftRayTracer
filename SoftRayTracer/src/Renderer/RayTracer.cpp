#include "RayTracer.h"
#include "../utils/Utils.h"
#include <random>

RayTracer::RayTracer(uint32_t width, uint32_t height, uint32_t depth, uint32_t samplerPerPixel, Window* context) :width(width), height(height), depth(depth), samplerPerPixel(samplerPerPixel), drawHandle(context) {}

void RayTracer::SetWorld(const HittableList& obj)
{
	world = obj;
}

void RayTracer::Draw()
{
	for (uint32_t y = 0; y < height; y++)
	{
		for (uint32_t x = 0; x < width; x++) 
		{			
			glm::vec3 color = { 0, 0, 0 };
			for (uint32_t s = 0; s < samplerPerPixel; s++)
			{
				float u = ((float)x + Tool::Random(0.0f, 1.0f)) / (width - 1.0f);
				float v = ((float)y + Tool::Random(0.0f, 1.0f)) / (height - 1.0f);
				Ray ray = camera.EmitRay(u, v);
				color += RayColor(ray, depth);
			}
			GammaCorrect(color);
			DrawPoint(x, y, color);
		}
	}
}

//range:[0.0, 1.0]
glm::vec3 RayTracer::RayColor(const Ray& ray, uint32_t depth)
{	
	HitRecord record;
	if (depth <= 0)
	{
		return { 0, 0, 0 };
	}
	if (world.Hit(ray, 0.001f, std::numeric_limits<float>::max(), record))
	{
		Ray scatter;
		glm::vec3 attenuation;
		if (record.material->Scatter(ray, record, attenuation, scatter))
		{
			glm::vec3 target = record.point + record.normal + Tool::RandomInUnitSphere();
			return attenuation * RayColor(scatter, depth - 1);
		} 		
		else {
			return { 0, 0, 0 };
		}
	}
	//remap [-1, 1] -> [0, 1]
	float t = (glm::normalize(ray.Direction()).y + 1.0f) * 0.5f;
	return BackGround(t);
}

glm::vec3 RayTracer::BackGround(float t)
{
	return glm::vec3(1.0) * t + (1.0f - t) * glm::vec3(0.3f, 0.5f, 1.0f);
}


void RayTracer::DrawPoint(uint32_t x, uint32_t y, const glm::vec3& color)
{
	drawHandle->DrawPoint(x, y, 255.0f * color);
}


void RayTracer::GammaCorrect(glm::vec3& color)
{
	float gamma = 1.0f / 2.0f;
	color.r = glm::pow(color.r / (float)samplerPerPixel, gamma);
	color.g = glm::pow(color.g / (float)samplerPerPixel, gamma);
	color.b = glm::pow(color.b / (float)samplerPerPixel, gamma);
}