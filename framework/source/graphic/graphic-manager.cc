#include "graphic-manager.h"

namespace kplge {
erroc GraphicManager::Initialize() { return KPL_NO_ERR; }
erroc GraphicManager::Finalize() { return KPL_NO_ERR; }
erroc GraphicManager::Tick() { return KPL_NO_ERR; }

bool GraphicManager::Clear() { return 1; }
bool GraphicManager::Draw() { return 1; }

}  // namespace kplge