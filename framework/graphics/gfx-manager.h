#pragma once
#include "manager.h"

namespace kplge {
class GfxManager : public IManager {
 public:
  ~GfxManager() override = default;

  int initialize() override = 0;
  int finalize() override = 0;

  int tick() override = 0;
};
}  // namespace kplge