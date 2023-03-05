#pragma once
#include <cstdint>

namespace kplge {
using erroc = uint16_t;
const erroc KPL_NO_ERR = 0;

const erroc WIN_ERR_CWND = 0x1001;  // Failed to create window.
const erroc WIN_ERR_DWND = 0x1002;  // Failed to destroy window.

const erroc GFX_ERR_INIT = 0x1101;  // Failed to initialize the graphics api.
const erroc GFX_ERR_FINA = 0x1102;  // Failed to finalize the graphics api.
const erroc GFX_ERR_RUNT = 0x1103;  // Graphics module runtime erroe.
}  // namespace kplge
