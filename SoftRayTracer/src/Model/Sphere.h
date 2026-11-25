#pragma once
#include "Hittable.h"
#include "../Renderer/Sampling.h"

class Sphere : public Hittable, public DirectionTarget {
public:
    Sphere(const glm::vec3& center, float radius, const std::shared_ptr<Material>& mat);
    Sphere(glm::vec3 start, glm::vec3 end, float radius, const std::shared_ptr<Material>& mat);
    bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) override;
    bool GetBoundingBox(BoundingBox& out) override;
    float Pdf(const glm::vec3& origin, const glm::vec3& direction, float time) const override;
    glm::vec3 Sample(const glm::vec3& origin, float time) const override;
private:
    glm::vec3 Center(float time) const { return start + time * displacement; }
    glm::vec3 start, displacement;
    float radius;
};
