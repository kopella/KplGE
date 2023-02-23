#pragma once
#include <vector>
#include <string>

#include "runtime-module.h"
#include "buffer.h"

#define KPL_OPEN_TEXT 0
#define KPL_OPEN_BINARY 1

namespace kplge {
class AssetLoader : IRuntimeModule {
 public:
  AssetLoader() = default;
  ~AssetLoader() override = default;
  using file_p = void*;

  erroc initialize() override;
  erroc finalize() override;
  erroc tick() override;

  // Search paths operations
  void clear_search_paths();
  bool add_search_path(const char* path);
  bool remove_search_path(const char* path);

  // Files operations
  Buffer sync_load_text(const char* path);
  Buffer sync_load_binary(const char* path);

 private:
  std::vector<std::string> m_search_paths{"","asset/","assets/"};

  bool open_file(file_p& fp, const char* path = "", int8_t mode = KPL_OPEN_BINARY, uint8_t level = 8);
  bool colse_file(file_p& fp);

  size_t get_file_size(file_p& f);
};

}  // namespace kplge
