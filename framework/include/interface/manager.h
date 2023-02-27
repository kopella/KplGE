#pragma once
#include "runtime-module.h"
#include "application.h"

namespace kplge {
class IManager : public IRuntimeModule {
 public:
  ~IManager() override = default;

  erroc Initialize() override = 0;
  erroc Finalize() override = 0;
  erroc Tick() override = 0;

  void SetAppPointer(IApplication* application) { application_ = application; }

 protected:
  IApplication* application_{};
};
}  // namespace kplge