#pragma once

#include "../interface/manager.h"
#include "scene-manager.h"

namespace kplge {
class GraphicManager : public IManager {
 public:
  SceneManager* p_sceneManager_;

  GraphicManager() = default;
  ~GraphicManager() override = default;

  erroc Initialize() override;
  erroc Finalize() override;
  erroc Tick() override;

  virtual bool Clear();
  virtual bool Draw();
};
}  // namespace kplge