#pragma once
#include "vector.h"
#include "matrix.h"

namespace kplutl {
Matrix4X4f build_rotation_matrix(
    const float yaw, const float pitch, const float roll);

Matrix4X4f build_rotation_matrix(
    const float s, const float i, const float j, const float k);
}  // namespace kplutl