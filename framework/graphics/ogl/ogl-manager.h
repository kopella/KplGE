#pragma once
#include "gfx-manager.h"

namespace kplge {
class OglManager : public GfxManager {
 public:
  ~OglManager() override;

  erroc initialize() override;
  erroc finalize() override;

  erroc tick() override;
};
}  // namespace kplge