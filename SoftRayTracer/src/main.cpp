#include "window/Window.h"
#include "Renderer/RayTracer.h"
#include "Model/Sphere.h"
#include "Material/Lambertian.h"
#include "Material/Metal.h"
#include "Material/Dielectric.h"
#include "utils/Utils.h"

constexpr uint32_t height = 1000;
constexpr float aspect = 3.0f / 2.0f;
constexpr uint32_t width = aspect * height;
constexpr uint32_t depth = 50;
constexpr uint32_t samplerPerPixel = 100;

HittableList RandomScene();
int main(int argc, char** argv)
{	
	Window window{ "SoftRenderer", width, height };
	std::shared_ptr<RayTracer> rt = std::make_shared<RayTracer>(width, height, depth, samplerPerPixel, &window);

	//auto diffuseMat = std::make_shared<Lambertian>(glm::vec3(0.2f, 0.8f, 0.1f));
	//auto groundMat = std::make_shared<Lambertian>(glm::vec3(0.2f, 0.2f, 0.2f));
	//auto metalMat = std::make_shared<Metal>(glm::vec3(0.8f, 0.1f, 0.2f), 0.0f);
 //   auto diedect = std::make_shared<Dielectric>(1.5f);
	//HittableList world;
	//world.AddObject(std::make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5f, diffuseMat));
	//world.AddObject(std::make_shared<Sphere>(glm::vec3(1, 0, -1), 0.5f, metalMat));
	//world.AddObject(std::make_shared<Sphere>(glm::vec3(0, 100.5, -1), 100, groundMat));
 //   world.AddObject(std::make_shared<Sphere>(glm::vec3(-1, 0, -1), 0.3f, diedect));
 //   world.AddObject(std::make_shared<Sphere>(glm::vec3(-1, 0, -1), -0.2f, diedect));
    HittableList world = RandomScene();
    Camera cam = Camera(glm::vec3(13, 2, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), aspect, 20.0f, 0.1f);
	rt->SetCamera(cam);
	rt->SetWorld(world);
	window.SetRayTracer(rt);
	window.Run();
	return 0;
}

HittableList RandomScene()
{
    HittableList world;
    auto ground_material = std::make_shared<Lambertian>(glm::vec3(0.5f, 0.5f, 0.5f));
    world.AddObject(std::make_shared<Sphere>(glm::vec3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = Tool::Random(0.0f, 1.0f);
            glm::vec3 center(a + 0.9 * Tool::Random(0.0f, 1.0f), 0.2, b + 0.9 * Tool::Random(0.0f, 1.0f));

            if ((center - glm::vec3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Tool::RandomVector(0.0f, 1.0f) * Tool::RandomVector(0.0f, 1.0f);
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.AddObject(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal                    
                    glm::vec3 albedo = Tool::RandomVector(0.5f, 1.0f);
                    auto fuzz = Tool::Random(0.0f, 0.5f);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.AddObject(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.AddObject(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.AddObject(std::make_shared<Sphere>(glm::vec3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(glm::vec3(0.4, 0.2, 0.1));
    world.AddObject(std::make_shared<Sphere>(glm::vec3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(glm::vec3(0.7, 0.6, 0.5), 0.0);
    world.AddObject(std::make_shared<Sphere>(glm::vec3(4, 1, 0), 1.0, material3));

    return world;
}