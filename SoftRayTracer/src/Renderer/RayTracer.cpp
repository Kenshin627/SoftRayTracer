#include "RayTracer.h"
#include <algorithm>
#include <limits>
#include <stdexcept>

RayTracer::RayTracer(int width, int height, int depth, int samples, uint32_t seed)
    : width(width), height(height), depth(depth), samples(samples), seed(seed)
{
    if (width < 1 || height < 1 || depth < 1 || samples < 1)
        throw std::invalid_argument("render dimensions, depth and samples must be positive");
}

std::vector<uint8_t> RayTracer::Render() const
{
    std::vector<uint8_t> pixels(size_t(width) * height * 3);
    int rows = int(std::sqrt(samples));
#ifdef _OPENMP
#pragma omp parallel for schedule(dynamic)
#endif
    for (int y = 0; y < height; ++y) {
        // A row owns its random stream even when workers finish out of order.
        std::seed_seq rowSeed{seed, uint32_t(y)};
        Tool::Generator().seed(rowSeed);
        for (int x = 0; x < width; ++x) {
            glm::vec3 color(0);
            int first = 0;
            for (int row = 0; row < rows; ++row) {
                // Each stratum has area 1/samples, including non-square sample counts.
                int columns = samples / rows + int(row < samples % rows);
                for (int col = 0; col < columns; ++col) {
                    float dx = (col + Tool::Random()) / columns;
                    float dy = (first + columns * Tool::Random()) / samples;
                    auto value = RayColor(camera->EmitRay((x+dx)/width, 1-(y+dy)/height), depth);
                    for (int c = 0; c < 3; ++c)
                        if (std::isfinite(value[c])) color[c] += value[c];
                }
                first += columns;
            }
            for (int c = 0; c < 3; ++c) {
                float gamma = std::sqrt(std::max(0.0f, color[c] / samples));
                pixels[(size_t(y) * width + x) * 3 + c] = uint8_t(255.999f * std::min(gamma, 1.0f));
            }
        }
    }
    return pixels;
}

glm::vec3 RayTracer::RayColor(const Ray& ray, int remaining) const
{
    if (remaining == 0) return glm::vec3(0);
    HitRecord rec;
    if (!world->Hit(ray, 0.001f, std::numeric_limits<float>::infinity(), rec)) {
        if (!skyGradient) return background;
        return glm::mix(glm::vec3(1), background, 0.5f * (ray.Direction().y + 1));
    }
    auto emitted = rec.material->Emitter(rec);
    Ray scattered;
    glm::vec3 attenuation;
    if (!rec.material->Scatter(ray, rec, attenuation, scattered)) return emitted;
    float weight = 1;
    if (importanceSampling && !targets.Empty() && rec.material->HasScatteringPdf()) {
        if (Tool::Random() < 0.5f)
            scattered = Ray(rec.point, targets.Sample(rec.point, ray.Time()), ray.Time());
        float scattering = rec.material->ScatteringPdf(rec, scattered);
        if (scattering <= 0) return emitted;
        float target = targets.Pdf(rec.point, scattered.Direction(), ray.Time());
        weight = scattering / (0.5f * (scattering + target));
    }
    return emitted + attenuation * weight * RayColor(scattered, remaining - 1);
}
