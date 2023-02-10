#include "wgl-manager.h"
#include "RHI/ogl/wgl-manager.h"

kplge::WglManager::WglManager(WinOglApplication* application) {
  this->application = application;
}

erroc kplge::WglManager::initialize() {

  return KPL_NO_ERR;
}

erroc kplge::WglManager::finalize() {

  return KPL_NO_ERR;
}

erroc kplge::WglManager::tick() {

  return KPL_NO_ERR;
}

int kplge::WglManager::create_context(){
  
}