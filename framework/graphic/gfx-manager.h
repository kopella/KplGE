#pragma once
#include "manager.h"

namespace kplge {
class GfxManager : public IManager {
 public:
  GfxManager() = default;
  ~GfxManager() override = default;

  erroc initialize() override = 0;
  erroc finalize() override = 0;

  erroc tick() override = 0;
};
}  // namespace kplge