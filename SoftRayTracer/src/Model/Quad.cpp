#include "Quad.h"
#include <limits>
#include <stdexcept>

Quad::Quad(glm::vec3 corner, glm::vec3 u, glm::vec3 v, std::shared_ptr<Material> mat)
    : Hittable(mat), corner(corner), u(u), v(v)
{
    auto cross = glm::cross(u, v);
    area = glm::length(cross);
    if (area == 0) throw std::invalid_argument("quad has zero area");
    normal = cross / area;
    dual = normal / area;
    auto low = corner + glm::min(u, glm::vec3(0)) + glm::min(v, glm::vec3(0));
    auto high = corner + glm::max(u, glm::vec3(0)) + glm::max(v, glm::vec3(0));
    bounds = BoundingBox(low - glm::vec3(0.0001f), high + glm::vec3(0.0001f));
}

bool Quad::Intersect(const glm::vec3& origin, const glm::vec3& direction,
                     float tMin, float tMax, float& t, glm::vec2& uv) const
{
    float cosine = glm::dot(normal, direction);
    if (std::abs(cosine) < 1e-8f) return false;
    t = glm::dot(normal, corner - origin) / cosine;
    if (t < tMin || t > tMax) return false;
    auto offset = origin + t * direction - corner;
    uv = {glm::dot(dual, glm::cross(offset, v)), glm::dot(dual, glm::cross(u, offset))};
    return uv.x >= 0 && uv.x <= 1 && uv.y >= 0 && uv.y <= 1;
}

bool Quad::Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec)
{
    float t;
    glm::vec2 uv;
    if (!Intersect(ray.Origin(), ray.Direction(), tMin, tMax, t, uv)) return false;
    rec.t = t;
    rec.uv = uv;
    rec.point = ray.At(t);
    rec.material = material;
    rec.SetNormal(ray, normal);
    return true;
}

float Quad::Pdf(const glm::vec3& origin, const glm::vec3& direction, float) const
{
    float t;
    glm::vec2 uv;
    if (!Intersect(origin, direction, 0.0001f, std::numeric_limits<float>::infinity(), t, uv)) return 0;
    return t * t / (area * std::abs(glm::dot(normal, direction)));
}

glm::vec3 Quad::Sample(const glm::vec3& origin, float) const
{
    float a = Tool::Random();
    float b = Tool::Random();
    return corner + a * u + b * v - origin;
}
