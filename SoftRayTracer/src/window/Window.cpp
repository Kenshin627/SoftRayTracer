#include "Window.h"
#include "../Renderer/RayTracer.h"
#include <stdexcept>

Window::Window(const char* title, int width, int height) : width(width), height(height)
{
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO) != 0) throw std::runtime_error(SDL_GetError());
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window) renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::string message = SDL_GetError();
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error(message);
    }
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::Run()
{
    auto pixels = rayTracer->Render();
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture(
        SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, width, height),
        SDL_DestroyTexture);
    if (!texture || SDL_UpdateTexture(texture.get(), nullptr, pixels.data(), width*3) != 0)
        throw std::runtime_error(SDL_GetError());
    SDL_Event event;
    do {
        SDL_RenderCopy(renderer, texture.get(), nullptr, nullptr);
        SDL_RenderPresent(renderer);
        if (!SDL_WaitEvent(&event)) throw std::runtime_error(SDL_GetError());
    } while (event.type != SDL_QUIT);
}
