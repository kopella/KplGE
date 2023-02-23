#pragma once
#include <cstdint>

/* Error Code */
using erroc = uint16_t;
#define KPL_NO_ERR 0

/* Platform Error */
#define WIN_ERR_CWND 0x1001  // Failed to create window.
#define WIN_ERR_DWND 0x1002  // Failed to destroy window.

/* Graphics Error */
#define GFX_ERR_INIT 0x1101  // Failed to initialize the graphics api.
#define GFX_ERR_FINA 0x1102  // Failed to finalize the graphics api.
#define GFX_ERR_RUNT 0x1103; // Graphics module runtime erroe.