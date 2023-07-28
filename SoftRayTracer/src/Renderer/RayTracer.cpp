#include "RayTracer.h"
#include "../utils/Utils.h"
#include <random>

RayTracer::RayTracer(uint32_t width, uint32_t height, uint32_t depth, uint32_t samplerPerPixel, Window* context) :width(width), height(height), depth(depth), samplerPerPixel(samplerPerPixel), drawHandle(context) {}

void RayTracer::SetWorld(const std::shared_ptr<Hittable>& obj)
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

	if (!world->Hit(ray, 0.0001f, std::numeric_limits<float>::infinity(), record))
	{
		//remap [-1, 1] -> [0, 1]
		//float t = (glm::normalize(ray.Direction()).y + 1.0f) * 0.5f;
		return BackGround();
	}
	
	Ray scatter;
	glm::vec3 attenuation;
	glm::vec3 emitColor = record.material->Emitter(0, 0, { 0, 0, 0 });
	if (!record.material->Scatter(ray, record, attenuation, scatter))
	{
		return emitColor;
	}
	return emitColor + attenuation * RayColor(scatter, depth - 1);
}

const glm::vec3& RayTracer::BackGround() const
{
	return background;
}


void RayTracer::DrawPoint(uint32_t x, uint32_t y, const glm::vec3& color)
{
	drawHandle->DrawPoint(x, y, 255.0f * color);
}


void RayTracer::GammaCorrect(glm::vec3& color)
{
	float gamma = 1.0f / 2.0f;
	if (color.r != color.r)
	{
		color.r = 0.0f;
	}if (color.g != color.g)
	{
		color.g = 0.0f;
	}
	if (color.b != color.b)
	{
		color.b = 0.0f;
	}
	color.r = glm::clamp(glm::pow(color.r / (float)samplerPerPixel, gamma), 0.0f, 1.0f);
	color.g = glm::clamp(glm::pow(color.g / (float)samplerPerPixel, gamma), 0.0f, 1.0f);
	color.b = glm::clamp(glm::pow(color.b / (float)samplerPerPixel, gamma), 0.0f, 1.0f);
}

void RayTracer::SetBackGround(const glm::vec3& color)
{
	background = color;
}