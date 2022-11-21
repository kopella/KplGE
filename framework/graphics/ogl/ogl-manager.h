#pragma once
#include "gfx-manager.h"

namespace kplge {
class OglManager : public GfxManager {
 public:
  ~OglManager() override;

  int initialize() override;
  int finalize() override;

  int tick() override;
};
}  // namespace kplge