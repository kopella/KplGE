#include <iostream>
#include <string>

#include "asset-loader.h"
#include "buffer.h"

int main() {
  kplge::AssetLoader assetLoader;

  kplge::Buffer buffer = assetLoader.sync_load_text("shader/f_shader.glsl");
  std::string test_res{reinterpret_cast<char*>(buffer.get_data())};

  std::cout << "Asset loader test result: \n" << test_res << std::endl;
  return 0;
}