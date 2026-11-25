#pragma once
#include "Quad.h"

class XYPlane : public Quad {
public:
    XYPlane(float x0, float x1, float y0, float y1, float z, const std::shared_ptr<Material>& mat);
};
