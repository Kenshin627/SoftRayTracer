#include "window/Window.h"
#include "Renderer/RayTracer.h"
#include "Model/Sphere.h"
#include "Material/DiffuseMaterial.h"
#include "Material/MetalMaterial.h"

constexpr uint32_t height = 768;
constexpr float aspect = 16.0f / 9.0f;
constexpr uint32_t width = aspect * height;
constexpr uint32_t depth = 50;
int main(int argc, char** argv)
{	
	Window window{ "SoftRenderer", width, height };
	std::shared_ptr<RayTracer> rt = std::make_shared<RayTracer>(width, height, depth, 50, &window);

	auto diffuseMat = std::make_shared<DiffuseMaterial>(glm::vec3(0.2f, 0.8f, 0.1f));
	auto groundMat = std::make_shared<DiffuseMaterial>(glm::vec3(0.2f, 0.2f, 0.2f));
	auto metalMat = std::make_shared<MetalMaterial>(glm::vec3(0.8f, 0.1f, 0.2f), 0.5f);
	HittableList world;
	world.AddObject(std::make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5f, diffuseMat));
	world.AddObject(std::make_shared<Sphere>(glm::vec3(1, 0, -1), 0.5f, metalMat));
	world.AddObject(std::make_shared<Sphere>(glm::vec3(0, 100.5, -1), 100, groundMat));
	Camera cam = Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 1.0f, aspect, 2.0f);
	rt->SetCamera(cam);
	rt->SetWorld(world);
	window.SetRayTracer(rt);
	window.Run();
	return 0;
}