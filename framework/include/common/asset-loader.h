#pragma once

#include <vector>
#include <string>

#include "../interface/runtime-module.h"
#include "buffer.h"

#define KPL_OPEN_TEXT 0
#define KPL_OPEN_BINARY 1

namespace kplge {
class AssetLoader : IRuntimeModule {
 public:
  AssetLoader() = default;
  ~AssetLoader() override = default;
  using file_p = void*;

  erroc Initialize() override;
  erroc Finalize() override;
  erroc Tick() override;

  // Search paths operations
  void ClearSearchPaths();
  bool AddSearchPath(const char* path);
  bool RemoveSearchPath(const char* path);

  // Files operations
  Buffer SyncLoadText(const char* path);
  Buffer SyncLoadBinary(const char* path);

 private:
  std::vector<std::string> search_paths_{"","asset/","assets/"};

  bool OpenFile(file_p& fp, const char* path = "", int8_t mode = KPL_OPEN_BINARY, uint8_t level = 8);
  bool ColseFile(file_p& fp);

  size_t GetFileSize(file_p& f);
};

}  // namespace kplge
