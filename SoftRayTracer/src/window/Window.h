#pragma once
#include <glm/glm.hpp>
#include <SDL.h>

class Window
{
public:
	Window(const char* title, uint32_t width, uint32_t height);
	~Window();
	void Destroy();
	void Run();
	void Clear();
private:
	SDL_Window* winHandle = nullptr;
	SDL_Renderer* drawHandle = nullptr;
	bool shounldClosed = false;
	glm::vec3 clearColor { 51, 51, 51 };
};