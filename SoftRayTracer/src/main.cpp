#include "window/Window.h"
#include "Renderer/RayTracer.h"
#include "Model/Sphere.h"
#include "Material/Lambertian.h"
#include "Material/Metal.h"
#include "Material/Dielectric.h"
#include "Material/DiffuseLight.h"
#include "utils/Utils.h"
#include "BVH/BvhNode.h"
#include "Model/XYPlane.h"
#include "Model/YZPlane.h"
#include "Model/XZPlane.h"

constexpr uint32_t height = 600;
constexpr float aspect = 1.0f;
constexpr uint32_t width = aspect * height;
constexpr uint32_t depth = 50;
constexpr uint32_t samplerPerPixel = 50;

std::shared_ptr<Hittable> RandomScene(std::shared_ptr<RayTracer> rt);
std::shared_ptr<Hittable> CornellBox(std::shared_ptr<RayTracer> rt);

int main(int argc, char** argv)
{	
	Window window{ "SoftRenderer", width, height };
	std::shared_ptr<RayTracer> rt = std::make_shared<RayTracer>(width, height, depth, samplerPerPixel, &window);
    std::shared_ptr<Hittable> world = CornellBox(rt);	
	window.SetRayTracer(rt);
	window.Run();
	return 0;
}

std::shared_ptr<Hittable> RandomScene(std::shared_ptr<RayTracer> rt)
{
    Camera cam = Camera(glm::vec3(13, 2, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), aspect, 20.0f, 0.1f, 10.0f);
    rt->SetCamera(cam);
    rt->SetBackGround({ 1.0f, 1.0f, 1.0f });
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
    auto bvhNode = std::make_shared<BvhNode>(world);
    rt->SetWorld(bvhNode);
    return bvhNode;
}

std::shared_ptr<Hittable> CornellBox(std::shared_ptr<RayTracer> rt)
{
    Camera cam = Camera(glm::vec3(278, 278, -800), glm::vec3(278, 278, 0), glm::vec3(0, 1, 0), aspect, 40.0f, 0.0f, 10.0f);
    rt->SetCamera(cam);
    rt->SetBackGround({ 0.0f, 0.0f, 0.0f });
    HittableList world;
    auto red = std::make_shared<Lambertian>(glm::vec3(1.0, .05, .05));
    auto white = std::make_shared<Lambertian>(glm::vec3(.73, .73, .73));
    auto green = std::make_shared<Lambertian>(glm::vec3(.12, 1.0, .15));
    auto light = std::make_shared<DiffuseLight>(glm::vec3(15.0f, 15.0f, 15.0f));

    world.AddObject(std::make_shared<YZPlane>(0, 555, 0, 555, 555, green));
    world.AddObject(std::make_shared<YZPlane>(0, 555, 0, 555, 0, red));
    world.AddObject(std::make_shared<XZPlane>(213, 343, 227, 332, 554, light));
    world.AddObject(std::make_shared<XZPlane>(0, 555, 0, 555, 555, white));
    world.AddObject(std::make_shared<XZPlane>(0, 555, 0, 555, 0, white));
    world.AddObject(std::make_shared<XYPlane>(0, 555, 0, 555, 555, white));

    //shared_ptr<hittable> box1 = make_shared<box>(point3(0, 0, 0), point3(165, 330, 165), white);
    //box1 = make_shared<rotate_y>(box1, 15);
    //box1 = make_shared<translate>(box1, vec3(265, 0, 295));
    //objects.add(box1);

    //shared_ptr<hittable> box2 = make_shared<box>(point3(0, 0, 0), point3(165, 165, 165), white);
    //box2 = make_shared<rotate_y>(box2, -18);
    //box2 = make_shared<translate>(box2, vec3(130, 0, 65));
    //objects.add(box2);
    auto bvhNode = std::make_shared<BvhNode>(world);
    rt->SetWorld(bvhNode);
    return bvhNode;
}