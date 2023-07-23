#include "Window.h"
#include <iostream>

Window::Window(const char* title, uint32_t width, uint32_t height)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "sdl init error" << std::endl;
	}

	winHandle = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	drawHandle = SDL_CreateRenderer(winHandle, -1, 0);
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

			//present
			SDL_RenderPresent(drawHandle);
		}
		else
		{
			shounldClosed = true;
		}

	}
}
void Window::Clear()
{
	SDL_SetRenderDrawColor(drawHandle, clearColor.r, clearColor.g, clearColor.b, 255);
	SDL_RenderClear(drawHandle);
}