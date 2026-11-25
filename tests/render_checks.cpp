#include "BVH/BvhNode.h"
#include "Material/Dielectric.h"
#include "Material/DiffuseLight.h"
#include "Material/IsoTropic.h"
#include "Material/Lambertian.h"
#include "Material/Metal.h"
#include "Model/Box.h"
#include "Model/ConstantMedium.h"
#include "Model/Quad.h"
#include "Model/RotationY.h"
#include "Model/Sphere.h"
#include "Model/Translation.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

using glm::vec3;
using std::make_shared;

static void Check(bool condition, const char* message)
{
    if (!condition) throw std::runtime_error(message);
}

static bool Near(float a, float b) { return std::abs(a-b) < 0.0001f; }

static void MovingSphere()
{
    auto ball = make_shared<Sphere>(vec3(0), vec3(4,0,0), 1, nullptr);
    HittableList objects;
    objects.AddObject(ball);
    BvhNode tree(objects);
    HitRecord hit;
    for (float time : {0.f, .5f, 1.f}) {
        vec3 origin(4*time,0,3);
        auto ray = Ray(origin, {0,0,-1}, time);
        Check(tree.Hit(ray, .001f, 10, hit) && Near(hit.t, 2), "moving BVH bounds");
        Check(Near(hit.uv.x, .25f) && Near(hit.uv.y, .5f), "sphere UV at +Z");
        float solidAngle = 2*Sampling::Pi*(1-std::sqrt(8.f/9));
        for (int i = 0; i < 256; ++i) {
            Ray sample(origin, ball->Sample(origin,time), time);
            Check(ball->Hit(sample,.001f,10,hit), "sphere cone missed its target");
            Check(Near(ball->Pdf(origin,sample.Direction(),time) * solidAngle,1), "sphere cone density");
        }
        Check(Near(ball->Pdf(origin,{0,0,1},time),0), "density behind the sphere");
        Check(Near(ball->Pdf({4*time,0,0},{0,1,0},time)*4*Sampling::Pi,1), "density inside sphere");
    }
}

static void Surfaces()
{
    auto light = make_shared<DiffuseLight>(vec3(3));
    Quad quad({0,0,0}, {2,0,0}, {1,2,0}, light);
    vec3 origin(1,.5f,2);
    HitRecord hit;
    Check(quad.Hit(Ray(origin,{0,0,-1}),.001f,10,hit), "skew quad hit");
    Check(Near(hit.uv.x,.375f) && Near(hit.uv.y,.25f), "skew quad UV");
    Check(Near(quad.Pdf(origin,{0,0,-1},0),1), "area to solid angle");
    Check(light->Emitter(hit) == vec3(3), "front emission");
    Check(quad.Hit(Ray({1,.5f,-2},{0,0,1}),.001f,10,hit) && light->Emitter(hit) == vec3(0),
          "back emission");
    Check(!quad.Hit(Ray({0,0,0},{1,0,0}),0,10,hit), "coplanar quad ray");
    for (int i = 0; i < 128; ++i) {
        Ray ray(origin,quad.Sample(origin,0));
        Check(quad.Hit(ray,.001f,10,hit) && quad.Pdf(origin,ray.Direction(),0) > 0, "quad sampling support");
    }

    auto box = make_shared<Box>(vec3(0),2,2,4,nullptr);
    Translation instance(make_shared<RotationY>(box,90), {3,0,0});
    Check(instance.Hit(Ray({3,0,0},{1,0,0}),.001f,10,hit), "inside box");
    Check(!hit.frontFace && Near(hit.t,2) && Near(hit.normal.x,-1), "transformed exit and box depth");
    Check(instance.Hit(Ray({0,0,0},{1,0,0}),.001f,10,hit) && hit.frontFace && Near(hit.t,1),
          "transformed entrance");
}

static void MaterialsAndMedium()
{
    Ray incoming({0,0,2},{0,0,-1},.75f), scattered;
    HitRecord hit;
    hit.point = vec3(0);
    hit.SetNormal(incoming,{0,0,1});
    Dielectric glass(1.5f);
    Metal metal(vec3(1),0);
    Lambertian diffuse(vec3(1));
    IsoTropic phase(vec3(1));
    Material* materials[] = {&glass, &metal, &diffuse, &phase};
    vec3 attenuation;
    for (auto mat : materials) {
        Check(mat->Scatter(incoming,hit,attenuation,scattered) && scattered.Time() == incoming.Time(),
              "scattered ray lost shutter time");
    }
    float meanCosine = 0, meanRadius2 = 0;
    for (int i = 0; i < 8192; ++i) {
        diffuse.Scatter(incoming,hit,attenuation,scattered);
        float cosine = scattered.Direction().z;
        Check(cosine >= 0 && Near(diffuse.ScatteringPdf(hit,scattered)*Sampling::Pi,cosine),
              "cosine PDF");
        meanCosine += cosine;
        auto offset = Tool::RandomInUnitDisk();
        meanRadius2 += glm::dot(offset,offset);
    }
    Check(std::abs(meanCosine/8192 - 2.f/3) < .02f, "cosine hemisphere distribution");
    Check(std::abs(meanRadius2/8192 - .5f) < .02f, "uniform aperture disk distribution");
    Check(Near(phase.ScatteringPdf(hit,scattered)*4*Sampling::Pi,1), "isotropic PDF");

    auto medium = make_shared<ConstantMedium>(make_shared<Sphere>(vec3(0),1,nullptr),.5f,vec3(1));
    HittableList objects;
    objects.AddObject(medium);
    BvhNode tree(objects);
    Tool::Generator().seed(31);
    int events = 0;
    for (int i = 0; i < 8192; ++i)
        events += tree.Hit(incoming,.001f,10,hit);
    Check(std::abs(events/8192.f - (1-std::exp(-1.f))) < .025f, "BVH leaf medium extinction");
}

int main()
{
    try {
        MovingSphere();
        Surfaces();
        MaterialsAndMedium();
    } catch (const std::exception& error) {
        std::cerr << error.what() << "\n";
        return 1;
    }
}
