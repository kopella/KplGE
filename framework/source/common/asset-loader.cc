#include "asset-loader.h"

#include <stdio.h>

#include "kpllogt.h"

namespace kplge {
erroc AssetLoader::Initialize() { return KPL_NO_ERR; }
erroc AssetLoader::Finalize() { return KPL_NO_ERR; }
erroc AssetLoader::Tick() { return KPL_NO_ERR; }

void AssetLoader::ClearSearchPaths() { search_paths_.clear(); }

bool AssetLoader::AddSearchPath(const char *path) {
  for (auto src = search_paths_.begin(); src != search_paths_.end(); src++) {
    if (*src == path) {
      return true;
    }
  }
  search_paths_.emplace_back(path);
  return true;
}

bool AssetLoader::RemoveSearchPath(const char *path) {
  for (auto src = search_paths_.begin(); src != search_paths_.end(); src++) {
    if (*src == path) {
      search_paths_.erase(src);
      return true;
    }
  }
  return true;
}

Buffer AssetLoader::SyncLoadText(const char *path) {
  file_p fp{};
  Buffer buffer;

  if (!OpenFile(fp, path, KPL_OPEN_TEXT)) {
    runtime_info("Can't open file '%s'", path);
  } else {
    size_t length = GetFileSize(fp);

    uint8_t *data = new uint8_t[length + 1];
    fread(data, length, 1, static_cast<FILE *>(fp));

    runtime_info("Read text file '%s', %zu bytes\n", path, length);

    data[length] = '\0';
    buffer.set_data(data, length + 1);

    ColseFile(fp);
  }
  return buffer;
}

Buffer AssetLoader::SyncLoadBinary(const char *path) {
  file_p fp{};
  Buffer buffer{};

  if (!OpenFile(fp, path, KPL_OPEN_BINARY)) {
    runtime_info("Can't open file '%s'", path);
  } else {
    size_t length = GetFileSize(fp);
    uint8_t *data = new uint8_t[length];
    fread(data, length, 1, static_cast<FILE *>(fp));

    runtime_info("Read binary file '%s', %zu bytes\n", path, length);

    buffer.set_data(data, length);
    ColseFile(fp);
  }
  return buffer;
}

bool AssetLoader::OpenFile(
    file_p &fp, const char *path, int8_t mode, uint8_t level) {
  std::string up_path{};
  std::string full_path{};
  for (int h = 0; h < level; h++) {
    for (std::string src : search_paths_) {
      full_path.assign(up_path);
      full_path.append(src);
      full_path.append(path);
      switch (mode) {
        case KPL_OPEN_TEXT:
          fp = fopen(full_path.data(), "r");
          break;
        case KPL_OPEN_BINARY:
          fp = fopen(full_path.data(), "rb");
          break;
      }
      if (fp) return 1;
    }
    up_path.append("../");
  }
  return 0;
}

bool AssetLoader::ColseFile(file_p &fp) {
  fclose((FILE *)fp);
  fp = nullptr;

  return 1;
}

size_t AssetLoader::GetFileSize(file_p &fp) {
  FILE *_fp = static_cast<FILE *>(fp);

  long pos = ftell(_fp);
  fseek(_fp, 0, SEEK_END);
  size_t length = ftell(_fp);
  fseek(_fp, pos, SEEK_SET);

  return length;
}
}  // namespace kplge
