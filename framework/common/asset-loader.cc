#include <stdio.h>

#include "kpl-log.h"

#include "asset-loader.h"
#include "buffer.h"

erroc kplge::AssetLoader::initialize() { return KPL_NO_ERR; }

erroc kplge::AssetLoader::finalize() { return KPL_NO_ERR; }

erroc kplge::AssetLoader::tick() { return KPL_NO_ERR; }

void kplge::AssetLoader::clear_search_paths() { m_search_paths.clear(); }

bool kplge::AssetLoader::add_search_path(const char *path) {
  for (auto src = m_search_paths.begin(); src != m_search_paths.end(); src++) {
    if (*src == path) {
      return true;
    }
  }
  m_search_paths.emplace_back(path);
  return true;
}

bool kplge::AssetLoader::remove_search_path(const char *path) {
  for (auto src = m_search_paths.begin(); src != m_search_paths.end(); src++) {
    if (*src == path) {
      m_search_paths.erase(src);
      return true;
    }
  }
  return true;
}

kplge::Buffer kplge::AssetLoader::sync_load_text(const char *path) {
  file_p fp{};
  Buffer buffer;

  if (!open_file(fp, path, KPL_OPEN_TEXT)) {
    runtime_info("Can't open file '%s'", path);
  } else {
    size_t length = get_file_size(fp);

    uint8_t *data = new uint8_t[length + 1];
    fread(data, length, 1, static_cast<FILE *>(fp));

    runtime_info("Read text file '%s', %zu bytes\n", path, length);

    data[length] = '\0';
    buffer.set_data(data, length + 1);

    colse_file(fp);
  }
  return buffer;
}

kplge::Buffer kplge::AssetLoader::sync_load_binary(const char *path) {
  file_p fp{};
  Buffer buffer;

  if (!open_file(fp, path, KPL_OPEN_BINARY)) {
    runtime_info("Can't open file '%s'", path);
  } else {
    size_t length = get_file_size(fp);
    uint8_t *data = new uint8_t[length];
    fread(data, length, 1, static_cast<FILE *>(fp));

    runtime_info("Read binary file '%s', %zu bytes\n", path, length);

    buffer.set_data(data, length);
    colse_file(fp);
  }
  return buffer;
}

bool kplge::AssetLoader::open_file(
    file_p &fp, const char *path, int8_t mode, uint8_t level) {
  std::string up_path{};
  std::string full_path{};
  for (int h = 0; h < level; h++) {
    for (std::string src : m_search_paths) {
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

bool kplge::AssetLoader::colse_file(file_p &fp) {
  fclose((FILE *)fp);
  fp = nullptr;

  return 1;
}

size_t kplge::AssetLoader::get_file_size(file_p &fp) {
  FILE *_fp = static_cast<FILE *>(fp);

  long pos = ftell(_fp);
  fseek(_fp, 0, SEEK_END);
  size_t length = ftell(_fp);
  fseek(_fp, pos, SEEK_SET);

  return length;
}