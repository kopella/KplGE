#pragma once

#include "config.h"

namespace kplutl {
#ifdef ENABLE_ISPC
namespace ispc {
extern "C" {
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

extern void cross(
    const float v3fin_a[3], const float v3fin_b[3], float v3fout[3]);
extern void transform(const float mfin[16], float vf[4]);

/* matrix */

extern void transpose(
    const float* mfin_a, float* mfout, const size_t row_count,
    const size_t col_count);
#ifdef ENABLE_ISPC
}
}  // namespace ispc
#endif
}  // namespace kplutl