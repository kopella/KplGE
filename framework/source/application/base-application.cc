#include "base-application.h"
#include "graphic-manager.h"

namespace kplge {
erroc BaseApplication::Initialize() { return KPL_NO_ERR; }
erroc BaseApplication::Finalize() { return KPL_NO_ERR; }
erroc BaseApplication::Tick() { return KPL_NO_ERR; }


void BaseApplication::RegisterManager(GraphicManager* manager){
    graphic_manager_ = manager;
    manager->SetAppPointer(this);
    managers.push_back(manager);
}
}  // namespace kplge