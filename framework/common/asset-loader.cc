#include <stdio.h>

#include "asset-loader.h"
#include "buffer.h"
#include "kpl-log.h"

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
  Buffer buff;

  if (!open_file(fp, path, KPL_OPEN_TEXT)) {
    info_to_console(
        (std::string{"Can't find file: "} + std::string{path}).data());
  } else {
    size_t length = get_file_size(fp);

    uint8_t *data = new uint8_t[length + 1];
    fread(data, length, 1, static_cast<FILE *>(fp));

    data[length] = '\0';
    for (int i = 0; i < length + 1; i++) printf("%02x\n", data[i]);
    buff.set_data(data, length);

    colse_file(fp);
  }
  return buff;
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