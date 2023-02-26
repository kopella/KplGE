#pragma once
#include <cassert>
#include <cmath>

#include <iostream>
#include <initializer_list>

#include "utils.h"
#include "vector.h"

namespace kplge {
template <typename T, size_t ROWS, size_t COLS>
struct MatrixMC {  // Matrix for mathematical calculations
  VectorMC<T, COLS> data[ROWS];

  MatrixMC<T, ROWS, COLS>() : data{} {}
  MatrixMC<T, ROWS, COLS>(T value) {
    for (size_t r = 0; r < ROWS; ++r) {
      for (size_t c = 0; c < COLS; ++c) {
        data[r][c] = value;
      }
    }
  }
  MatrixMC<T, ROWS, COLS>(
      std::initializer_list<std::initializer_list<const T>> list) {
    assert(list.size() <= ROWS);
    size_t i = 0;
    for (auto sub_list : list) {
      assert(sub_list.size() <= COLS);
      size_t j = 0;
      for (auto value : sub_list) {
        data[i][j++] = value;
      }
      i++;
    }
  }
  template <typename S>
  explicit MatrixMC<T, ROWS, COLS>(const S* source) {
    for (size_t r = 0; r < ROWS; ++r) {
      for (size_t c = 0; c < COLS; ++c) {
        data[r][c] = (T)source[r][c];
      }
    }
  }
  template <typename S>
  explicit MatrixMC<T, ROWS, COLS>(const MatrixMC<S, ROWS, COLS>& source) {
    for (size_t r = 0; r < ROWS; ++r) {
      for (size_t c = 0; c < COLS; ++c) {
        data[r][c] = (T)source[r][c];
      }
    }
  }

  VectorMC<T, COLS>& operator[](int row_index) { return data[row_index]; }

  operator T*() { return &data[0][0]; };

  operator const T*() const { return static_cast<const T*>(&data[0][0]); };
};

/* type defines */

using Matrix3X3f = MatrixMC<float, 3, 3>;
using Matrix4X4f = MatrixMC<float, 4, 4>;

/* inline functions */

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_add(
    const MatrixMC<T, ROWS, COLS>& min_a, const MatrixMC<T, ROWS, COLS>& min_b,
    MatrixMC<T, ROWS, COLS>& mout) {
#ifdef ENABLE_ISPC
  ispc::add_foreach(min_a, min_b, mout, ROWS * COLS);
#else
  add_foreach(min_a, min_b, mout, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_sub(
    const MatrixMC<T, ROWS, COLS>& min_a, const MatrixMC<T, ROWS, COLS>& min_b,
    MatrixMC<T, ROWS, COLS>& mout) {
#ifdef ENABLE_ISPC
  ispc::sub_foreach(min_a, min_b, mout, ROWS * COLS);
#else
  sub_foreach(min_a, min_b, mout, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_mul(
    const MatrixMC<T, ROWS, COLS>& min_a, const MatrixMC<T, ROWS, COLS>& min_b,
    MatrixMC<T, ROWS, COLS>& mout) {
#ifdef ENABLE_ISPC
  ispc::mul_foreach(min_a, min_b, mout, ROWS * COLS);
#else
  mul_foreach(min_a, min_b, mout, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_div(
    const MatrixMC<T, ROWS, COLS>& min_a, const MatrixMC<T, ROWS, COLS>& min_b,
    MatrixMC<T, ROWS, COLS>& mout) {
#ifdef ENABLE_ISPC
  ispc::div_foreach(min_a, min_b, mout, ROWS * COLS);
#else
  div_foreach(min_a, min_b, mout, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_abs(
    const MatrixMC<T, ROWS, COLS>& min, MatrixMC<T, ROWS, COLS>& mout) {
#ifdef ENABLE_ISPC
  ispc::abs_foreach(min, mout, ROWS * COLS);
#else
  abs_foreach(min, min_b, mout, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_sqrt(
    const MatrixMC<T, ROWS, COLS>& min, MatrixMC<T, ROWS, COLS>& mout) {
#ifdef ENABLE_ISPC
  ispc::sqrt_foreach(min, mout, ROWS * COLS);
#else
  sqrt_foreach(min, mout, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_transpose(
    const MatrixMC<T, ROWS, COLS>& min, MatrixMC<T, ROWS, COLS>& mout) {
#ifdef ENABLE_ISPC
  ispc::transpose(min, mout, ROWS, COLS);
#else
  transpose(min, mout, ROWS, COLS);
#endif
}

/* operators */

/* + */

template <typename T, size_t ROWS, size_t COLS>
MatrixMC<T, ROWS, COLS> operator+(
    const MatrixMC<T, ROWS, COLS>& lhs, const MatrixMC<T, ROWS, COLS>& rhs) {
  MatrixMC<T, ROWS, COLS> res;
  matrix_add(lhs, rhs, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixMC<T, ROWS, COLS> operator+(
    const MatrixMC<T, ROWS, COLS>& lhs, const T scalar) {
  MatrixMC<T, ROWS, COLS> res;
  matrix_add(lhs, res, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixMC<T, ROWS, COLS> operator+(
    const T scalar, const MatrixMC<T, ROWS, COLS>& rhs) {
  MatrixMC<T, ROWS, COLS> res;
  matrix_add(res, rhs, res);
  return res;
}

/* - */

template <typename T, size_t ROWS, size_t COLS>
MatrixMC<T, ROWS, COLS> operator-(
    const MatrixMC<T, ROWS, COLS>& lhs, const MatrixMC<T, ROWS, COLS>& rhs) {
  MatrixMC<T, ROWS, COLS> res;
  matrix_sub(lhs, rhs, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixMC<T, ROWS, COLS> operator-(
    const MatrixMC<T, ROWS, COLS>& lhs, const T scalar) {
  MatrixMC<T, ROWS, COLS> res;
  matrix_sub(lhs, res, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixMC<T, ROWS, COLS> operator-(
    const T scalar, const MatrixMC<T, ROWS, COLS>& rhs) {
  MatrixMC<T, ROWS, COLS> res;
  matrix_sub(res, rhs, res);
  return res;
}

/* * */

template <typename T, size_t ROWS, size_t COLS>
MatrixMC<T, ROWS, COLS> operator*(
    const MatrixMC<T, ROWS, COLS>& lhs, const MatrixMC<T, ROWS, COLS>& rhs) {
  MatrixMC<T, ROWS, COLS> res;
  matrix_mul(lhs, rhs, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixMC<T, ROWS, COLS> operator*(
    const MatrixMC<T, ROWS, COLS>& lhs, const T scalar) {
  MatrixMC<T, ROWS, COLS> res;
  matrix_mul(lhs, res, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixMC<T, ROWS, COLS> operator*(
    const T scalar, const MatrixMC<T, ROWS, COLS>& rhs) {
  MatrixMC<T, ROWS, COLS> res;
  matrix_mul(res, rhs, res);
  return res;
}

/* / */

template <typename T, size_t ROWS, size_t COLS>
MatrixMC<T, ROWS, COLS> operator/(
    const MatrixMC<T, ROWS, COLS>& lhs, const MatrixMC<T, ROWS, COLS>& rhs) {
  MatrixMC<T, ROWS, COLS> res;
  matrix_div(lhs, rhs, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixMC<T, ROWS, COLS> operator/(
    const MatrixMC<T, ROWS, COLS>& lhs, const T scalar) {
  MatrixMC<T, ROWS, COLS> res;
  matrix_div(lhs, res, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixMC<T, ROWS, COLS> operator/(
    const T scalar, const MatrixMC<T, ROWS, COLS>& rhs) {
  MatrixMC<T, ROWS, COLS> res;
  matrix_div(res, rhs, res);
  return res;
}

/* free functions */

template <typename T, size_t ROWS, size_t COLS>
MatrixMC<T, ROWS, COLS> abs(const MatrixMC<T, ROWS, COLS>& mat) {
  MatrixMC<T, ROWS, COLS> res;
  matrix_abs(mat, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixMC<T, ROWS, COLS> transpose(const MatrixMC<T, ROWS, COLS>& mat) {
  MatrixMC<T, COLS, ROWS> res;
  matrix_transpose(mat, res);
  return res;
}

/* stream */

template <typename T, size_t ROWS, size_t COLS>
std::istream& operator>>(std::istream& in, MatrixMC<T, ROWS, COLS>& mat) {
  for (size_t r = 0; r < ROWS; ++r) in >> mat[r];
  return in;
}

template <typename T, size_t ROWS, size_t COLS>
std::ostream& operator<<(std::ostream& out, MatrixMC<T, ROWS, COLS>& mat) {
  out << std::endl;
  for (size_t r = 0; r < ROWS; ++r) out << mat[r] << std::endl;
  return out;
}

template <typename T, size_t ROWS, size_t COLS>
std::ostream& operator<<(std::ostream& out, MatrixMC<T, ROWS, COLS>&& mat) {
  out << std::endl;
  for (size_t r = 0; r < ROWS; ++r) out << mat[r] << std::endl;
  return out;
}

}  // namespace kplge