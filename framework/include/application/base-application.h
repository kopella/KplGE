#pragma once

#include <vector>

#include "../interface/application.h"
#include "../interface/manager.h"
#include "graphic-config.h"
#include "graphic-manager.h"

namespace kplge {
class BaseApplication : public IApplication {
 public:
  BaseApplication() = default;
  ~BaseApplication() override = default;

  explicit BaseApplication(GraphicConfig& graphic_config)
      : graphic_config_(graphic_config) {}

  erroc Initialize() override;
  erroc Finalize() override;
  erroc Tick() override;

  bool CheckQuitTag() { return tag_quit_; }

  void RegisterManager(GraphicManager* manager);

  GraphicManager* GetGraphicManager() { return graphic_manager_; }

 protected:
  bool tag_quit_{false};
  void ChangeQuitTag() { tag_quit_ = true; }

  GraphicConfig graphic_config_;

  GraphicManager* graphic_manager_{};

  std::vector<IManager*> managers_;
};
}  // namespace kplge