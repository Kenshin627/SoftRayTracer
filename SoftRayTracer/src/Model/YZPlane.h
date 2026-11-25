#pragma once
#include "Quad.h"

class YZPlane : public Quad {
public:
    YZPlane(float y0, float y1, float z0, float z1, float x, const std::shared_ptr<Material>& mat);
};
