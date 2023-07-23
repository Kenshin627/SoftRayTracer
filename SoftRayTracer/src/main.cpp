#include "window/Window.h"
#include "Renderer/RayTracer.h"
#include "Model/Sphere.h"

constexpr uint32_t height = 768;
constexpr float aspect = 16.0f / 9.0f;
constexpr uint32_t width = aspect * height;
constexpr uint32_t depth = 50;
int main(int argc, char** argv)
{
	Window window{ "SoftRenderer", width, height };
	std::shared_ptr<RayTracer> rt = std::make_shared<RayTracer>(width, height, depth, 50, &window);
	HittableList world;
	world.AddObject(std::make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5f));
	world.AddObject(std::make_shared<Sphere>(glm::vec3(0, 100.5, -1), 100));
	Camera cam = Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 1.0f, aspect, 2.0f);
	rt->SetCamera(cam);
	rt->SetWorld(world);
	window.SetRayTracer(rt);
	window.Run();
	return 0;
}