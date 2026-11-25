#include "XYPlane.h"

XYPlane::XYPlane(float x0, float x1, float y0, float y1, float z, const std::shared_ptr<Material>& mat)
    : Quad({x0, y0, z}, {x1-x0, 0, 0}, {0, y1-y0, 0}, mat) {}
