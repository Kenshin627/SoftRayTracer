#include "XZPlane.h"

XZPlane::XZPlane(float x0, float x1, float z0, float z1, float y, const std::shared_ptr<Material>& mat)
    : Quad({x0, y, z0}, {0, 0, z1-z0}, {x1-x0, 0, 0}, mat) {}
