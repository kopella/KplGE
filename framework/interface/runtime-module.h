#pragma once

namespace kplge {
class IRuntimeModule {
 public:
  virtual ~IRuntimeModule() = default;

  virtual int initialize() = 0;
  virtual int finalize() = 0;

  virtual int tick() = 0;
};
}  // namespace kplge