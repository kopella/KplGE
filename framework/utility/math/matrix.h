#pragma once
#include <cmath>
#include <array>
#include <iostream>
#include <initializer_list>

#include "kpl-math.h"
#include "vector.h"

namespace kplge {
template <typename T, size_t ROWS, size_t COLS>
struct MatrixMC {  // Matrix for mathematical calculations
  VectorMC<T, COLS> data[ROWS];

  VectorMC<T, COLS>& operator[](int row_index) { return data[row_index]; }

  operator T*() { return &data[0][0]; };
};

/* inline functions */

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_add(
    const MatrixMC<T, ROWS, COLS>& vin_a, const MatrixMC<T, ROWS, COLS>& vin_b,
    MatrixMC<T, ROWS, COLS>& vout) {
#ifdef ENABLE_ISPC
  ispc::add_foreach(vin_a, vin_b, vout, ROWS * COLS);
#else
  kplge::add_foreach(vin_a, vin_b, vout, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_sub(
    const MatrixMC<T, ROWS, COLS>& vin_a, const MatrixMC<T, ROWS, COLS>& vin_b,
    MatrixMC<T, ROWS, COLS>& vout) {
#ifdef ENABLE_ISPC
  ispc::sub_foreach(vin_a, vin_b, vout, ROWS * COLS);
#else
  kplge::sub_foreach(vin_a, vin_b, vout, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_mul(
    const MatrixMC<T, ROWS, COLS>& vin_a, const MatrixMC<T, ROWS, COLS>& vin_b,
    MatrixMC<T, ROWS, COLS>& vout) {
#ifdef ENABLE_ISPC
  ispc::mul_foreach(vin_a, vin_b, vout, ROWS * COLS);
#else
  kplge::mul_foreach(vin_a, vin_b, vout, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_div(
    const MatrixMC<T, ROWS, COLS>& vin_a, const MatrixMC<T, ROWS, COLS>& vin_b,
    MatrixMC<T, ROWS, COLS>& vout) {
#ifdef ENABLE_ISPC
  ispc::div_foreach(vin_a, vin_b, vout, ROWS * COLS);
#else
  kplge::div_foreach(vin_a, vin_b, vout, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_abs(
    const MatrixMC<T, ROWS, COLS>& vin, MatrixMC<T, ROWS, COLS>& vout) {
#ifdef ENABLE_ISPC
  ispc::abs_foreach(vin, vout, ROWS * COLS);
#else
  kplge::abs_foreach(vin_a, vin_b, vout, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_sqrt(
    const MatrixMC<T, ROWS, COLS>& vin, MatrixMC<T, ROWS, COLS>& vout) {
#ifdef ENABLE_ISPC
  ispc::sqrt_foreach(vin, vout, ROWS * COLS);
#else
  kplge::sqrt_foreach(vin_a, vin_b, vout, ROWS * COLS);
#endif
}

}  // namespace kplge