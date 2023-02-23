#pragma once

#include <vcruntime.h>
#include "kpl-config.h"
#include "kpl-define.h"

#include "vector.h"

#ifdef ENABLE_ISPC
namespace ispc {
extern "C" {
#else
namespace kplge {
#endif
/* basic */
extern void add_foreach(
    const float* in_a, const float* in_b, float* out, const size_t count);
extern void sub_foreach(
    const float* in_a, const float* in_b, float* out, const size_t count);
extern void mul_foreach(
    const float* in_a, const float* in_b, float* out, const size_t count);
extern void div_foreach(
    const float* in_a, const float* in_b, float* out, const size_t count);

/* vector */
extern void cross_product(
    const float in_a[3], const float in_b[3], float out[3]);
extern void normalize(const float* in_a, const size_t count, float length);
#ifdef ENABLE_ISPC
}
}  // namespace ispc
#else
}  // namespace kplge
#endif
