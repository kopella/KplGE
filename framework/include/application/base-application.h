#pragma once
#include <vector>

#include "application.h"
#include "gfx-manager.h"
#include "gfx-config.h"

namespace kplge {
class BaseApplication : public IApplication {
 public:
  BaseApplication() = default;
  ~BaseApplication() override = default;

  explicit BaseApplication(GraphicConfig& gfx_config);

  erroc initialize() override;
  erroc finalize() override;

  erroc tick() override;

  bool check_quit_tag();

 protected:
  void change_quit_tag();

  GfxManager* gfx_manager;

 private:
  bool quit_tag;

  GraphicConfig gfx_config_;
};
}  // namespace kplge