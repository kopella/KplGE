#pragma once
#include "../interface/manager.h"

namespace kplge {
class GraphicManager : public IManager {
 public:
  GraphicManager() = default;
  ~GraphicManager() override = default;

  erroc Initialize() override;
  erroc Finalize() override;
  erroc Tick() override;
};
}  // namespace kplge