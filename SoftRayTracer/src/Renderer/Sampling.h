#pragma once
#include "../utils/Utils.h"
#include <memory>
#include <vector>

namespace Sampling {
constexpr float Pi = 3.14159265358979323846f;

// Rotate a local sample around +Z into the frame with pole n.
inline glm::vec3 ToWorld(const glm::vec3& local, const glm::vec3& n)
{
    glm::vec3 helper = std::abs(n.x) > 0.9f ? glm::vec3(0,1,0) : glm::vec3(1,0,0);
    glm::vec3 tangent = glm::normalize(glm::cross(helper, n));
    return local.x * tangent + local.y * glm::cross(n, tangent) + local.z * n;
}

inline glm::vec3 AroundPole(float z, float radial, const glm::vec3& pole)
{
    float phi = 2 * Pi * Tool::Random();
    return ToWorld({radial * std::cos(phi), radial * std::sin(phi), z}, pole);
}

inline glm::vec3 CosineHemisphere(const glm::vec3& normal)
{
    float r2 = Tool::Random();
    return AroundPole(std::sqrt(1-r2), std::sqrt(r2), normal);
}
}

// Density per unit solid angle. Directions passed to Pdf are normalized.
class DirectionTarget {
public:
    virtual ~DirectionTarget() = default;
    virtual float Pdf(const glm::vec3& origin, const glm::vec3& direction, float time) const = 0;
    virtual glm::vec3 Sample(const glm::vec3& origin, float time) const = 0;
};

class SamplingTargets {
public:
    void Add(std::shared_ptr<DirectionTarget> target) { objects.push_back(target); }
    bool Empty() const { return objects.empty(); }
    glm::vec3 Sample(const glm::vec3& origin, float time) const {
        return objects[Tool::RandomInt(0, int(objects.size()) - 1)]->Sample(origin, time);
    }
    float Pdf(const glm::vec3& origin, const glm::vec3& direction, float time) const {
        float sum = 0;
        for (const auto& object : objects) sum += object->Pdf(origin, direction, time);
        return sum / objects.size();
    }
private:
    std::vector<std::shared_ptr<DirectionTarget>> objects;
};
