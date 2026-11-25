#pragma once
#include <memory>
#include <SDL.h>

class RayTracer;
class Window {
public:
    Window(const char* title, int width, int height);
    ~Window();
    void SetRayTracer(std::shared_ptr<RayTracer> rt) { rayTracer = rt; }
    void Run();
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    int width, height;
    std::shared_ptr<RayTracer> rayTracer;
};
