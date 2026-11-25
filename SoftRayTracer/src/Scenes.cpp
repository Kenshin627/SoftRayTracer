#include "Scenes.h"
#include "Model/Quad.h"
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
#include "Model/Translation.h"
#include "Model/RotationY.h"
#include "Model/Box.h"
#include "Model/ConstantMedium.h"

static void RandomScene(RayTracer& rt, float aspect)
{
    std::shared_ptr<Camera> cam = std::make_shared<Camera>(glm::vec3(13, 2, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), aspect, 20.0f, 0.1f, 10.0f);
    rt.SetCamera(cam);
    rt.SetBackGround({0.5f, 0.7f, 1.0f});
    rt.SetSkyGradient(true);
    HittableList world;
    auto ground_material = std::make_shared<Lambertian>(glm::vec3(0.5f, 0.5f, 0.5f));
    world.AddObject(std::make_shared<Sphere>(glm::vec3(0, -1000, 0), 1000, ground_material));
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = Tool::Random(0.0f, 1.0f);
            glm::vec3 center(a + 0.9 * Tool::Random(0.0f, 1.0f), 0.2, b + 0.9 * Tool::Random(0.0f, 1.0f));

            if (glm::length(center - glm::vec3(4, 0.2, 0)) > 0.9) {
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
    rt.SetWorld(bvhNode);
}


using glm::vec3;
using std::make_shared;

static void SetView(RayTracer& rt, float aspect, vec3 eye, vec3 target, float fov, float aperture = 0)
{
    rt.SetCamera(make_shared<Camera>(eye, target, vec3(0,1,0), aspect, fov, aperture, glm::length(target-eye)));
}

static void Cornell(RayTracer& rt, float aspect, bool smoke)
{
    SetView(rt, aspect, {278,278,-800}, {278,278,0}, 40);
    HittableList world;
    auto red = make_shared<Lambertian>(vec3(.65f,.05f,.05f));
    auto white = make_shared<Lambertian>(vec3(.73f));
    auto green = make_shared<Lambertian>(vec3(.12f,.45f,.15f));
    auto light = make_shared<DiffuseLight>(vec3(smoke ? 7.f : 15.f));
    world.AddObject(make_shared<YZPlane>(0,555,0,555,555,green));
    world.AddObject(make_shared<YZPlane>(0,555,0,555,0,red));
    world.AddObject(make_shared<XZPlane>(0,555,0,555,555,white));
    world.AddObject(make_shared<XZPlane>(0,555,0,555,0,white));
    world.AddObject(make_shared<XYPlane>(0,555,0,555,555,white));
    auto lamp = smoke
        ? make_shared<Quad>(vec3(113,554,127), vec3(330,0,0), vec3(0,0,305), light)
        : make_shared<Quad>(vec3(213,554,227), vec3(130,0,0), vec3(0,0,105), light);
    world.AddObject(lamp);
    rt.AddTarget(lamp);
    std::shared_ptr<Hittable> tall = make_shared<Box>(vec3(82.5f,165,82.5f),165,330,165,white);
    tall = make_shared<Translation>(make_shared<RotationY>(tall,15), vec3(265,0,295));
    if (smoke) {
        std::shared_ptr<Hittable> shortBox = make_shared<Box>(vec3(82.5f),165,165,165,white);
        shortBox = make_shared<Translation>(make_shared<RotationY>(shortBox,-18), vec3(130,0,65));
        world.AddObject(make_shared<ConstantMedium>(tall,.01f,vec3(0)));
        world.AddObject(make_shared<ConstantMedium>(shortBox,.01f,vec3(1)));
    } else {
        world.AddObject(tall);
        auto glass = make_shared<Sphere>(vec3(190,90,190),90,make_shared<Dielectric>(1.5f));
        world.AddObject(glass);
        rt.AddTarget(glass);
    }
    rt.SetWorld(make_shared<BvhNode>(world));
}

static void Studio(RayTracer& rt, float aspect, const std::filesystem::path& earthMap, bool motion)
{
    SetView(rt, aspect, {0,2.1f,8.4f}, {0,1,0}, 29);
    rt.SetBackGround({.56f,.74f,1});
    rt.SetSkyGradient(true);
    HittableList world;
    auto checks = make_shared<CheckerTexture>(.6f, make_shared<SolidColor>(vec3(.19f,.25f,.28f)),
                                                   make_shared<SolidColor>(vec3(.75f,.78f,.70f)));
    world.AddObject(make_shared<Quad>(vec3(-100,0,100), vec3(200,0,0), vec3(0,0,-200),
                                       make_shared<Lambertian>(checks)));
    if (motion) {
        auto clay = make_shared<Lambertian>(vec3(.83f,.19f,.065f));
        world.AddObject(make_shared<Sphere>(vec3(-1.45f,.82f,0),.82f,clay));
        world.AddObject(make_shared<Sphere>(vec3(.7f,.82f,0),vec3(2.25f,.82f,0),.82f,clay));
    } else {
        auto marble = make_shared<Lambertian>(make_shared<MarbleTexture>(4));
        auto earth = make_shared<Lambertian>(make_shared<ImageTexture>(earthMap.string()));
        world.AddObject(make_shared<Sphere>(vec3(-1.25f,1.05f,0),1.05f,earth));
        world.AddObject(make_shared<Sphere>(vec3(1.25f,1.05f,0),1.05f,marble));
    }
    rt.SetWorld(make_shared<BvhNode>(world));
}

// Ground boxes and clustered spheres each have their own BVH.
static void FinalScene(RayTracer& rt, float aspect, const std::filesystem::path& earthMap)
{
    SetView(rt, aspect, {478,278,-600}, {278,278,0}, 40);
    HittableList world, ground, cluster;
    auto green = make_shared<Lambertian>(vec3(.48f,.83f,.53f));
    for (int x = 0; x < 20; ++x) {
        for (int z = 0; z < 20; ++z) {
            int h = Tool::RandomInt(1,101);
            ground.AddObject(make_shared<Box>(vec3(100*x-950,.5f*h,100*z-950),100,h,100,green));
        }
    }
    world.AddObject(make_shared<BvhNode>(ground));
    auto lamp = make_shared<Quad>(vec3(123,554,147),vec3(300,0,0),vec3(0,0,265),
                                  make_shared<DiffuseLight>(vec3(7)));
    world.AddObject(lamp);
    rt.AddTarget(lamp);
    auto glass = make_shared<Dielectric>(1.5f);
    world.AddObject(make_shared<Sphere>(vec3(400,400,200),vec3(430,400,200),50,
                                        make_shared<Lambertian>(vec3(.7f,.3f,.1f))));
    world.AddObject(make_shared<Sphere>(vec3(260,150,45),50,glass));
    world.AddObject(make_shared<Sphere>(vec3(0,150,145),50,make_shared<Metal>(vec3(.8f,.8f,.9f),1)));
    auto boundary = make_shared<Sphere>(vec3(360,150,145),70,glass);
    world.AddObject(boundary);
    world.AddObject(make_shared<ConstantMedium>(boundary,.2f,vec3(.2f,.4f,.9f)));
    world.AddObject(make_shared<ConstantMedium>(make_shared<Sphere>(vec3(0),5000,glass),.0001f,vec3(1)));
    world.AddObject(make_shared<Sphere>(vec3(400,200,400),100,
                        make_shared<Lambertian>(make_shared<ImageTexture>(earthMap.string()))));
    world.AddObject(make_shared<Sphere>(vec3(220,280,300),80,make_shared<Lambertian>(make_shared<MarbleTexture>(.2f))));
    auto white = make_shared<Lambertian>(vec3(.73f));
    for (int i = 0; i < 1000; ++i)
        cluster.AddObject(make_shared<Sphere>(Tool::RandomVector(0,165),10,white));
    world.AddObject(make_shared<Translation>(make_shared<RotationY>(make_shared<BvhNode>(cluster),15),
                                             vec3(-100,270,395)));
    rt.SetWorld(make_shared<BvhNode>(world));
}

static void Quads(RayTracer& rt, float aspect)
{
    SetView(rt, aspect, {0,0,9}, {0,0,0}, 55);
    rt.SetBackGround({.72f,.8f,1});
    HittableList world;
    auto panel = [&](vec3 corner, vec3 u, vec3 v, vec3 color) {
        world.AddObject(make_shared<Quad>(corner, u, v, make_shared<Lambertian>(color)));
    };
    panel({-3,-2,3},{0,0,-4},{0,4,0},{.9f,.2f,.15f});
    panel({-2,-2,0},{4,0,0},{0,4,0},{.17f,.67f,.35f});
    panel({3,-2,-1},{0,0,4},{0,4,0},{.22f,.4f,.9f});
    panel({-2,3,1},{4,0,0},{0,0,4},{.94f,.58f,.12f});
    panel({-2,-3,4},{4,.35f,0},{.5f,0,-4},{.3f,.78f,.83f});
    rt.SetWorld(make_shared<BvhNode>(world));
}

void BuildScene(RayTracer& rt, const std::string& name, float aspect, const std::filesystem::path& earthMap)
{
    if (name == "random") RandomScene(rt, aspect);
    else if (name == "cornell" || name == "smoke") Cornell(rt, aspect, name == "smoke");
    else if (name == "textures" || name == "motion") Studio(rt, aspect, earthMap, name == "motion");
    else if (name == "final") FinalScene(rt, aspect, earthMap);
    else if (name == "quads") Quads(rt, aspect);
    else throw std::invalid_argument("unknown scene: " + name);
}
