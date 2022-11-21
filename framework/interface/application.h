#pragma once
#include "runtime-module.h"

namespace kplge {
class IApplication : public IRuntimeModule {
 public:
  ~IApplication() override = default;

  int initialize() override = 0;
  int finalize() override = 0;

  int tick() override = 0;

  virtual bool check_quit_tag() = 0;
};
}  // namespace kplge