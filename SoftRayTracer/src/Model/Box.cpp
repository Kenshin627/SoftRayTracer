#include "Box.h"
#include "Quad.h"

Box::Box(const glm::vec3& center, uint32_t width, uint32_t height, uint32_t depth,
         const std::shared_ptr<Material>& mat) : Hittable(mat)
{
    glm::vec3 size(width, height, depth);
    auto lo = center - size * 0.5f;
    auto hi = center + size * 0.5f;
    aabb = BoundingBox(lo, hi);
    glm::vec3 x(size.x, 0, 0), y(0, size.y, 0), z(0, 0, size.z);
    faces.AddObject(std::make_shared<Quad>(lo, y, x, mat));
    faces.AddObject(std::make_shared<Quad>(lo, x, z, mat));
    faces.AddObject(std::make_shared<Quad>(lo, z, y, mat));
    faces.AddObject(std::make_shared<Quad>(hi, -x, -y, mat));
    faces.AddObject(std::make_shared<Quad>(hi, -z, -x, mat));
    faces.AddObject(std::make_shared<Quad>(hi, -y, -z, mat));
}

bool Box::Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec)
{
    return faces.Hit(ray, tMin, tMax, rec);
}

bool Box::GetBoundingBox(BoundingBox& out)
{
    out = aabb;
    return true;
}
