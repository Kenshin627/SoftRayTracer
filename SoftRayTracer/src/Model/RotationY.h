#pragma once
#include "Hittable.h"

class RotationY:public Hittable {
public:
    RotationY(std::shared_ptr<Hittable> p, double angle);
    virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) override;
    virtual bool GetBoundingBox(BoundingBox& output_box) override {
        output_box = bbox;
        return hasbox;
    }

public:
    std::shared_ptr<Hittable> target;
    double sinTheta;
    double cosTheta;
    bool hasbox;
    BoundingBox bbox;
};