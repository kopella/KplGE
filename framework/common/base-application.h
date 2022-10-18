#pragma once
#include <vector>

#include "application.h"
#include "manager.h"
#include "gfx-config.h"

namespace kplge {
class BaseApplication : public IApplication {
 public:
  BaseApplication() = default;
  explicit BaseApplication(GraphicsConfiguration& gfx_config);
  ~BaseApplication() override = default;

  int initialize() override;
  int finalize() override;

  int tick() override;

  void create_window() override;

  bool check_quit_tag() override;

 private:
  bool quit_tag;

  GraphicsConfiguration gfx_config_;

  std::vector<IManager*> managers;
};
}  // namespace kplge