#include "Sphere.h"
#include <stdexcept>

Sphere::Sphere(const glm::vec3& center, float radius, const std::shared_ptr<Material>& mat)
    : Sphere(center, center, radius, mat) {}

Sphere::Sphere(glm::vec3 start, glm::vec3 end, float radius, const std::shared_ptr<Material>& mat)
    : Hittable(mat), start(start), displacement(end - start), radius(radius)
{
    if (radius <= 0) throw std::invalid_argument("sphere radius must be positive");
}

bool Sphere::Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec)
{
    auto center = Center(ray.Time());
    glm::dvec3 oc = glm::dvec3(center) - glm::dvec3(ray.Origin());
    glm::dvec3 d(ray.Direction());
    double a = glm::dot(d, d);
    double h = glm::dot(oc, d);
    double discriminant = h*h - a * (glm::dot(oc, oc) - double(radius)*radius);
    if (discriminant < 0) return false;
    double delta = std::sqrt(discriminant);
    double root = (h - delta) / a;
    if (root < tMin || root > tMax) {
        root = (h + delta) / a;
        if (root < tMin || root > tMax) return false;
    }
    rec.t = float(root);
    rec.point = ray.At(rec.t);
    glm::vec3 outward = glm::normalize(glm::vec3(root*d - oc));
    rec.SetNormal(ray, outward);
    rec.uv = {(std::atan2(-outward.z, outward.x) + Sampling::Pi) / (2*Sampling::Pi),
              std::acos(glm::clamp(-outward.y, -1.0f, 1.0f)) / Sampling::Pi};
    rec.material = material;
    return true;
}

bool Sphere::GetBoundingBox(BoundingBox& out)
{
    out = BoundingBox(glm::min(start, Center(1)) - radius, glm::max(start, Center(1)) + radius);
    return true;
}

// 1 - cos(theta_max), rationalized to retain precision for distant spheres.
static float ConeHeight(float ratioSquared)
{
    return ratioSquared / (1 + std::sqrt(1 - ratioSquared));
}

glm::vec3 Sphere::Sample(const glm::vec3& origin, float time) const
{
    auto axis = Center(time) - origin;
    float distance2 = glm::dot(axis, axis);
    if (distance2 <= radius*radius) return Tool::RandomInUnitSphere();
    float height = Tool::Random() * ConeHeight(radius*radius / distance2);
    return Sampling::AroundPole(1-height, std::sqrt(height*(2-height)), glm::normalize(axis));
}

float Sphere::Pdf(const glm::vec3& origin, const glm::vec3& direction, float time) const
{
    auto axis = Center(time) - origin;
    float distance2 = glm::dot(axis, axis);
    if (distance2 <= radius*radius) return 1 / (4 * Sampling::Pi);
    auto perpendicular = glm::cross(axis, direction);
    if (glm::dot(axis, direction) <= 0 || glm::dot(perpendicular, perpendicular) > radius*radius) return 0;
    return 1 / (2 * Sampling::Pi * ConeHeight(radius*radius / distance2));
}
