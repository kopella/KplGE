#pragma once
#include <vector>

#include "application.h"
#include "manager.h"
#include "gfx-config.h"

namespace kplge {
class BaseApplication : public IApplication {
 public:
  BaseApplication() = default;
  explicit BaseApplication(GfxConfig& gfx_config);
  ~BaseApplication() override = default;

  erroc initialize() override;
  erroc finalize() override;

  erroc tick() override;

  bool check_quit_tag();

 protected:
  void change_quit_tag();

 private:
  bool quit_tag;
  std::vector<IManager*> managers;

  GfxConfig gfx_config_;
};
}  // namespace kplge