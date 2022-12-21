#pragma once
#include "gfx-manager.h"

#if defined(_WIN32)
#include <windows.h>
#endif

#include "GL/gl.h"
#include "GL/glext.h"

namespace kplge {
class OglManager : public GfxManager {
 public:
  erroc initialize() override;
  erroc finalize() override;

  erroc tick() override;
};
}  // namespace kplge