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
	void SetCamera(std::shared_ptr<Camera> c) { camera = c; }
	void SetWorld(const std::shared_ptr<Hittable>& obj);
	void Draw();
	glm::vec3 RayColor(const Ray& ray, uint32_t depth);
	void DrawPoint(uint32_t x, uint32_t y, const glm::vec3& color);
	const glm::vec3& BackGround() const ;
	void SetBackGround(const glm::vec3& background);
	void GammaCorrect(glm::vec3& color);
private:
	std::shared_ptr<Camera> camera = nullptr;
	std::shared_ptr<Hittable> world = nullptr;
	uint32_t width;
	uint32_t height;
	uint32_t depth;
	uint32_t samplerPerPixel;
	Window* drawHandle;
	glm::vec3 background = { 0.0f, 0.0f, 0.0f };
};