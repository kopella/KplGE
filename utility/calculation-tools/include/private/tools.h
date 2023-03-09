#pragma once
#include "vector.h"
#include "matrix.h"

namespace kplutl {
Matrix4X4f build_scale_matrix(const float x, const float y, const float z);

Matrix4X4f build_rotation_matrix(
    const float yaw, const float pitch, const float roll);

Matrix4X4f build_rotation_matrix(
    const float s, const float i, const float j, const float k);

Matrix4X4f build_translation_matrix(
    const float x, const float y, const float z);
}  // namespace kplutl