#include "Window.h"
#include "../Renderer/RayTracer.h"
#include <iostream>

Window::Window(const char* title, uint32_t width, uint32_t height)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "sdl init error" << std::endl;
	}

	winHandle = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	drawHandle = SDL_CreateRenderer(winHandle, -1, 0);
	glm::mat3 reflectTrans = {
		{ 1,  0, 0 },
		{ 0, -1, 0 },
		{ 0,  0, 1 }
	};
	glm::mat3 translationY = {
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, height, 1 }
	};
	transform = translationY * reflectTrans;
}

Window::~Window()
{
	Destroy();
}

void Window::Destroy()
{
	SDL_DestroyRenderer(drawHandle);
	SDL_DestroyWindow(winHandle);
}

void Window::Run()
{
	while (!shounldClosed)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		if (event.type != SDL_QUIT)
		{
			//clear
			Clear();
			//draw
			rayTracer->Draw();
			//present
			SDL_RenderPresent(drawHandle);
		}
		else
		{
			shounldClosed = true;
		}

	}
}

void Window::DrawPoint(uint32_t x, uint32_t y, const glm::vec3& color)
{
	SDL_SetRenderDrawColor(drawHandle, color.r, color.g, color.b, 255);
	glm::vec3 p = transform * glm::vec3(x, y, 1);
	SDL_RenderDrawPoint(drawHandle, p.x, p.y);
}

void Window::Clear()
{
	SDL_SetRenderDrawColor(drawHandle, clearColor.r, clearColor.g, clearColor.b, 255);
	SDL_RenderClear(drawHandle);
}