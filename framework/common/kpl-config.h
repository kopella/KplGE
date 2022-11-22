#pragma once
#include <stdint.h>
#define KPL_DEBUG

/* Error Code */
using erroc = uint16_t;
#define KPL_NO_ERR 0

/* Platform Error */
#define WIN_ERR_CWND 0x1001  // Failed to create window.
#define WIN_ERR_DWND 0x1002  // Failed to destroy window.

/* Graphics Error */
#define GFX_ERR_