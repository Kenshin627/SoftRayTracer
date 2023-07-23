#include "RayTracer.h"

RayTracer::RayTracer(uint32_t width, uint32_t height, Window* context) :width(width), height(height), drawHandle(context) {}

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
			float u = (float)x / (width - 1.0f);
			float v = (float)y / (height - 1.0f);
			Ray ray = camera.EmitRay(u, v);
			HitRecord record;
			if (world.Hit(ray, 0.001f, std::numeric_limits<float>::max(), record))
			{
				drawHandle->DrawPoint(x, y, { (record.normal.x + 1.0f) * 0.5f * 255, (record.normal.y + 1.0f) * 0.5f * 255, (record.normal.z + 1.0f) * 0.5f * 255 });
			}
			else
			{
				drawHandle->DrawPoint(x, y, { 0, 0, 0 });
			}
		}
	}
}