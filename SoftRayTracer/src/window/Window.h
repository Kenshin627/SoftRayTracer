#pragma once
#include <glm/glm.hpp>
#include <SDL.h>
#include <memory>

class RayTracer;
class Window
{
public:
	Window(const char* title, uint32_t width, uint32_t height);
	void SetRayTracer(const std::shared_ptr<RayTracer>& rt) { rayTracer = rt; }
	~Window();
	void Destroy();
	void Run();
	void DrawPoint(uint32_t x, uint32_t y, const glm::vec3& color);
	void Clear();
private:
	SDL_Window* winHandle = nullptr;
	SDL_Renderer* drawHandle = nullptr;
	bool shounldClosed = false;
	glm::vec3 clearColor { 51, 51, 51 };
	std::shared_ptr<RayTracer> rayTracer;
	glm::mat3 transform;
};