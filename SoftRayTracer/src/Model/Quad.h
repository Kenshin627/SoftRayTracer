#pragma once
#include "Hittable.h"
#include "../Renderer/Sampling.h"

class Quad : public Hittable, public DirectionTarget {
public:
    Quad(glm::vec3 corner, glm::vec3 u, glm::vec3 v, std::shared_ptr<Material> mat);
    bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) override;
    bool GetBoundingBox(BoundingBox& out) override { out = bounds; return true; }
    float Pdf(const glm::vec3& origin, const glm::vec3& direction, float time) const override;
    glm::vec3 Sample(const glm::vec3& origin, float time) const override;
private:
    bool Intersect(const glm::vec3& origin, const glm::vec3& direction,
                   float tMin, float tMax, float& t, glm::vec2& uv) const;
    glm::vec3 corner, u, v, normal, dual;
    float area;
    BoundingBox bounds;
};
