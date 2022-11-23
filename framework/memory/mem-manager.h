#pragma once
#include "manager.h"

namespace kplge {
class MemManager : public IManager {
 public:
  erroc initialize() override = 0;
  erroc finalize() override = 0;

  erroc tick() override = 0;
};
}  // namespace kplge