#include "RotationY.h"

RotationY::RotationY(std::shared_ptr<Hittable> p, double angle):target(p)
{
    auto radians = glm::radians(angle);
    sinTheta = glm::sin(radians);
    cosTheta = glm::cos(radians);
    hasbox = target->GetBoundingBox(bbox);
    constexpr auto infinity = std::numeric_limits<float>::infinity();
    glm::vec3 min(infinity, infinity, infinity);
    glm::vec3 max(-infinity, -infinity, -infinity);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto x = i * bbox.Max().x + (1 - i) * bbox.Min().x;
                auto y = j * bbox.Max().y + (1 - j) * bbox.Min().y;
                auto z = k * bbox.Max().z + (1 - k) * bbox.Min().z;
                auto newx = cosTheta * x + sinTheta * z;
                auto newz = -sinTheta * x + cosTheta * z;
                glm::vec3 tester(newx, y, newz);
                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }
    bbox = BoundingBox(min, max);
}

bool RotationY::Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec)
{
    auto origin = ray.Origin();
    auto direction = ray.Direction();

    origin[0] = cosTheta * ray.Origin()[0] - sinTheta * ray.Origin()[2];
    origin[2] = sinTheta * ray.Origin()[0] + cosTheta * ray.Origin()[2];

    direction[0] = cosTheta * ray.Direction()[0] - sinTheta * ray.Direction()[2];
    direction[2] = sinTheta * ray.Direction()[0] + cosTheta * ray.Direction()[2];

    Ray rotated_r(origin, direction);

    if (!target->Hit(rotated_r, tMin, tMax, rec))
        return false;

    auto p = rec.point;
    auto normal = rec.normal;

    p[0] = cosTheta * rec.point[0] + sinTheta * rec.point[2];
    p[2] = -sinTheta * rec.point[0] + cosTheta * rec.point[2];

    normal[0] = cosTheta * rec.normal[0] + sinTheta * rec.normal[2];
    normal[2] = -sinTheta * rec.normal[0] + cosTheta * rec.normal[2];

    rec.point = p;
    rec.SetNormal(rotated_r, normal);

    return true;
}