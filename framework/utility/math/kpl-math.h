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
    const float* vfin_a, const float* vfin_b, float* vfout, const size_t count);

extern void sub_foreach(
    const float* vfin_a, const float* vfin_b, float* vfout, const size_t count);

extern void mul_foreach(
    const float* vfin_a, const float* vfin_b, float* vfout, const size_t count);

extern void div_foreach(
    const float* vfin_a, const float* vfin_b, float* vfout, const size_t count);

extern void pow_foreach(
    const float* vfin_a, const float* vfin_b, float* vfout, const size_t count);

extern void abs_foreach(const float* vfin, float* vfout, const size_t count);

extern void sqrt_foreach(const float* vfin, float* vfout, const size_t count);

/* vector */

extern void cross_product(
    const float v3fin_a[3], const float v3fin_b[3], float v3fout[3]);

/* matrix */
#ifdef ENABLE_ISPC
}
}  // namespace ispc
#else
}  // namespace kplge
#endif
