#pragma once
#include "gfx-manager.h"

namespace kplge {
class OglManager : public GfxManager {
 public:
  erroc initialize() override;
  erroc finalize() override;

  erroc tick() override;
};
}  // namespace kplge