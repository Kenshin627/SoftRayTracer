#include "YZPlane.h"

YZPlane::YZPlane(float y0, float y1, float z0, float z1, float x, const std::shared_ptr<Material>& mat)
    : Quad({x, y0, z0}, {0, y1-y0, 0}, {0, 0, z1-z0}, mat) {}
