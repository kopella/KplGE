#pragma once

#include <vector>

#include "../interface/application.h"
#include "../interface/manager.h"
#include "graphic-config.h"
#include "graphic-manager.h"
#include "scene-manager.h"

namespace kplge {
class BaseApplication : public IApplication {
 public:
  BaseApplication() = default;
  ~BaseApplication() override = default;

  explicit BaseApplication(GraphicConfig& graphic_config)
      : graphicConfig_(graphic_config) {}

  erroc Initialize() override;
  erroc Finalize() override;
  erroc Tick() override;

  bool CheckQuitTag() { return tagQuit_; }

  void RegisterManager(GraphicManager* manager);
  void RegisterManager(SceneManager* manager);

  GraphicManager* GetGraphicManager() { return p_graphicManager_; }
  SceneManager* GetSceneManager() { return p_sceneManager_; }

 protected:
  bool tagQuit_{false};
  void ChangeQuitTag() { tagQuit_ = true; }

  GraphicConfig graphicConfig_;

  GraphicManager* p_graphicManager_;
  SceneManager* p_sceneManager_;

  std::vector<IManager*> managers_;
};
}  // namespace kplge