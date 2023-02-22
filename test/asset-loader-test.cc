#include <fstream>
#include <iostream>
#include <string>

#include "asset-loader.h"
#include "buffer.h"

int main() {
  kplge::AssetLoader assetLoader;

  kplge::Buffer buff = assetLoader.sync_load_text("test/test.txt");
  std::string res{reinterpret_cast<char*>(buff.get_data())};

  std::ofstream outfile;
  outfile.open("res");

  outfile << res << std::endl;

  return 0;
}