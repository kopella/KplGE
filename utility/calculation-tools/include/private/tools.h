#pragma once
#include "vector.h"
#include "matrix.h"

namespace kplutl {
template <typename T>
MatrixCT<T, 4, 4> build_scale_matrix(const T x, const T y, const T z) {
  return MatrixCT<T, 4, 4>{
      {x, 0, 0, 0}, {0, y, 0, 0}, {0, 0, z, 0}, {0, 0, 0, 1}};
}

template <typename T>
MatrixCT<T, 4, 4> build_rotation_matrix(
    const T yaw, const T pitch, const T roll) {
  T cYaw = std::cos(yaw);
  T cPitch = std::cos(pitch);
  T cRoll = std::cos(roll);

  T sYaw = std::sin(yaw);
  T sPitch = std::sin(pitch);
  T sRoll = std::sin(roll);

  return MatrixCT<T, 4, 4>{
      {(cRoll * cYaw) + (sRoll * sPitch * sYaw), (sRoll * cPitch),
       (cRoll * -sYaw) + (sRoll * sPitch * cYaw), 0.0f},
      {(-sRoll * cYaw) + (cRoll * sPitch * sYaw), (cRoll * cPitch),
       (sRoll * sYaw) + (cRoll * sPitch * cYaw), 0.0f},
      {(cPitch * sYaw), -sPitch, (cPitch * cYaw), 0.0f},
      {0.0f, 0.0f, 0.0f, 1.0f}};
}

template <typename T>
MatrixCT<T, 4, 4> build_rotation_matrix(
    const T x, const T y, const T z, const T w) {
  // First row of the rotation matrix
  T r00 = 2.0 * (w * w + x * x) - 1.0;
  T r01 = 2.0 * (x * y - w * z);
  T r02 = 2.0 * (x * z + w * y);

  // Second row of the rotation matrix
  T r10 = 2.0 * (x * y + w * z);
  T r11 = 2.0 * (w * w + y * y) - 1.0;
  T r12 = 2.0 * (y * z - w * x);

  // Third row of the rotation matrix
  T r20 = 2.0 * (x * z - w * y);
  T r21 = 2.0 * (y * z + w * x);
  T r22 = 2.0 * (w * w + z * z) - 1.0;

  return MatrixCT<T, 4, 4>{
      {r00, r01, r02, 0}, {r10, r11, r12, 0}, {r20, r21, r22, 0}, {0, 0, 0, 1}};
}

template <typename T>
MatrixCT<T, 4, 4> build_translation_matrix(const T x, const T y, const T z) {
  return MatrixCT<T, 4, 4>{
      {1, 0, 0, x}, {0, 1, 0, y}, {0, 0, 1, z}, {0, 0, 0, 1}};
}
}  // namespace kplutl