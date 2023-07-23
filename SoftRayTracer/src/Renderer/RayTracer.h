#pragma once
#include "../Camera/Camera.h"
#include "../Model/HittableList.h"
#include "../window/Window.h"
#include <cstdint>
#include <vector>

class RayTracer
{
public:
	RayTracer(uint32_t width, uint32_t height, Window* context);
	void SetCamera(const Camera& c) { camera = c; }
	void SetWorld(const HittableList& obj);
	void Draw();
private:
	Camera camera;
	HittableList world;
	uint32_t width;
	uint32_t height;
	Window* drawHandle;
};