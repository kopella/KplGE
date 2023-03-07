#include "base-application.h"
#include "graphic-manager.h"
#include "scene-manager.h"

namespace kplge {
erroc BaseApplication::Initialize() { return KPL_NO_ERR; }
erroc BaseApplication::Finalize() { return KPL_NO_ERR; }
erroc BaseApplication::Tick() { return KPL_NO_ERR; }

void BaseApplication::RegisterManager(GraphicManager* manager) {
  p_graphicManager_ = manager;
  manager->SetAppPointer(this);
  managers_.push_back(manager);
}

void BaseApplication::RegisterManager(SceneManager* manager) {
  p_sceneManager_ = manager;
  p_graphicManager_->p_sceneManager_ = manager;
  manager->SetAppPointer(this);
  managers_.push_back(manager);
}
}  // namespace kplge