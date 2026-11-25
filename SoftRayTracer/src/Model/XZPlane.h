#pragma once
#include "Quad.h"

class XZPlane : public Quad {
public:
    XZPlane(float x0, float x1, float z0, float z1, float y, const std::shared_ptr<Material>& mat);
};
