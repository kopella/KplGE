#include <iostream>
#include <string>

#include "asset-loader.h"
#include "buffer.h"

using namespace kplge;

int main() {
  AssetLoader assetLoader;

  Buffer buffer = assetLoader.SyncLoadText("shader/f_shader.glsl");
  std::string test_res{reinterpret_cast<char*>(buffer.get_data())};

  std::cout << "Asset loader test result: \n" << test_res << std::endl;
  return 0;
}