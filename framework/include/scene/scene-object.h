#pragma once

#include "kplidgen.h"

namespace kplge {
class SceneObject {
 protected:
  kplutl::Guid guid_{};

 public:
  SceneObject() = default;
  virtual ~SceneObject() = default;
};
}  // namespace kplge