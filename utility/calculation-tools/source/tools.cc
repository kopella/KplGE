#include "tools.h"
#include "matrix.h"

namespace kplutl {
Matrix4X4f build_rotation_matrix(
    const float yaw, const float pitch, const float roll) {
  float cYaw = std::cos(yaw);
  float cPitch = std::cos(pitch);
  float cRoll = std::cos(roll);

  float sYaw = std::sin(yaw);
  float sPitch = std::sin(pitch);
  float sRoll = std::sin(roll);

  return Matrix4X4f{
      {(cRoll * cYaw) + (sRoll * sPitch * sYaw), (sRoll * cPitch),
       (cRoll * -sYaw) + (sRoll * sPitch * cYaw), 0.0f},
      {(-sRoll * cYaw) + (cRoll * sPitch * sYaw), (cRoll * cPitch),
       (sRoll * sYaw) + (cRoll * sPitch * cYaw), 0.0f},
      {(cPitch * sYaw), -sPitch, (cPitch * cYaw), 0.0f},
      {0.0f, 0.0f, 0.0f, 1.0f}};
}

Matrix4X4f build_rotation_matrix(
    const float a, const float x, const float y, const float z) {
  return Matrix4X4f{
      {(a * a) + (x * x) - (y * y) - (z * z), (2 * x * y) + (2 * a * z),
       (2 * x * z) - (2 * a * y), 0.0f},
      {(2 * x * y) - (2 * a * z), (a * a) - (x * x) + (y * y) - (z * z),
       (2 * y * z) + (2 * a * x), 0.0f},
      {(2 * x * z) + (2 * a * y), (2 * y * z) - (2 * a * x),
       (a * a) - (x * x) - (y * y) + (z * z), 0.0f},
      {0.0f, 0.0f, 0.0f, 1.0f}};
}
}  // namespace kplutl