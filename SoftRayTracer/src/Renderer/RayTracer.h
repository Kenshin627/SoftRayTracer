#pragma once
#include "../Camera/Camera.h"
#include "../Model/HittableList.h"
#include "../window/Window.h"
#include <cstdint>
#include <vector>

class RayTracer
{
public:
	RayTracer(uint32_t width, uint32_t height, uint32_t depth, uint32_t samplerPerPixel, Window* context);
	void SetCamera(const Camera& c) { camera = c; }
	void SetWorld(const std::shared_ptr<Hittable>& obj);
	void Draw();
	glm::vec3 RayColor(const Ray& ray, uint32_t depth);
	void DrawPoint(uint32_t x, uint32_t y, const glm::vec3& color);
	glm::vec3 BackGround(float t);
	void GammaCorrect(glm::vec3& color);
private:
	Camera camera;
	std::shared_ptr<Hittable> world;
	uint32_t width;
	uint32_t height;
	uint32_t depth;
	uint32_t samplerPerPixel;
	Window* drawHandle;
};