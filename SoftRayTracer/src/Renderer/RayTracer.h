#pragma once
#include "../Camera/Camera.h"
#include "../Model/HittableList.h"
#include "Sampling.h"
#include <cstdint>
#include <vector>

class RayTracer {
public:
    RayTracer(int width, int height, int depth, int samples, uint32_t seed);
    void SetCamera(std::shared_ptr<Camera> c) { camera = c; }
    void SetWorld(std::shared_ptr<Hittable> obj) { world = obj; }
    void SetBackGround(glm::vec3 color) { background = color; }
    void SetSkyGradient(bool enabled) { skyGradient = enabled; }
    void AddTarget(std::shared_ptr<DirectionTarget> target) { targets.Add(target); }
    void SetImportanceSampling(bool enabled) { importanceSampling = enabled; }
    std::vector<uint8_t> Render() const;
    glm::vec3 RayColor(const Ray& ray, int remaining) const;
private:
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Hittable> world;
    SamplingTargets targets;
    int width, height, depth, samples;
    uint32_t seed;
    glm::vec3 background{0};
    bool skyGradient = false;
    bool importanceSampling = true;
};
