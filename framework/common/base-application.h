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

  int initialize() override;
  int finalize() override;

  int tick() override;
  bool check_quit_tag() override;

 private:
  bool quit_tag;
  std::vector<IManager*> managers;

  GfxConfig gfx_config_;
};
}  // namespace kplge