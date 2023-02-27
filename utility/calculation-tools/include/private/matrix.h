#pragma once
#include <cassert>
#include <cmath>

#include <iostream>
#include <initializer_list>

#include "utils.h"
#include "vector.h"

namespace kplutl {
template <typename T, size_t ROWS, size_t COLS>
struct MatrixCT { 
  VectorGC<T, COLS> data[ROWS];

  MatrixCT<T, ROWS, COLS>() : data{} {}
  MatrixCT<T, ROWS, COLS>(T value) {
    for (size_t r = 0; r < ROWS; ++r) {
      for (size_t c = 0; c < COLS; ++c) {
        data[r][c] = value;
      }
    }
  }
  MatrixCT<T, ROWS, COLS>(
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
  explicit MatrixCT<T, ROWS, COLS>(const S* source) {
    for (size_t r = 0; r < ROWS; ++r) {
      for (size_t c = 0; c < COLS; ++c) {
        data[r][c] = (T)source[r][c];
      }
    }
  }
  template <typename S>
  explicit MatrixCT<T, ROWS, COLS>(const MatrixCT<S, ROWS, COLS>& source) {
    for (size_t r = 0; r < ROWS; ++r) {
      for (size_t c = 0; c < COLS; ++c) {
        data[r][c] = (T)source[r][c];
      }
    }
  }

  VectorGC<T, COLS>& operator[](int row_index) { return data[row_index]; }

  operator T*() { return &data[0][0]; };

  operator const T*() const { return static_cast<const T*>(&data[0][0]); };
};

/* type defines */

using Matrix3X3f = MatrixCT<float, 3, 3>;
using Matrix4X4f = MatrixCT<float, 4, 4>;

/* inline functions */

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_add(
    const MatrixCT<T, ROWS, COLS>& min_a, const MatrixCT<T, ROWS, COLS>& min_b,
    MatrixCT<T, ROWS, COLS>& mout) {
#ifdef ENABLE_ISPC
  ispc::add_foreach(min_a, min_b, mout, ROWS * COLS);
#else
  add_foreach(min_a, min_b, mout, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_sub(
    const MatrixCT<T, ROWS, COLS>& min_a, const MatrixCT<T, ROWS, COLS>& min_b,
    MatrixCT<T, ROWS, COLS>& mout) {
#ifdef ENABLE_ISPC
  ispc::sub_foreach(min_a, min_b, mout, ROWS * COLS);
#else
  sub_foreach(min_a, min_b, mout, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_mul(
    const MatrixCT<T, ROWS, COLS>& min_a, const MatrixCT<T, ROWS, COLS>& min_b,
    MatrixCT<T, ROWS, COLS>& mout) {
#ifdef ENABLE_ISPC
  ispc::mul_foreach(min_a, min_b, mout, ROWS * COLS);
#else
  mul_foreach(min_a, min_b, mout, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_div(
    const MatrixCT<T, ROWS, COLS>& min_a, const MatrixCT<T, ROWS, COLS>& min_b,
    MatrixCT<T, ROWS, COLS>& mout) {
#ifdef ENABLE_ISPC
  ispc::div_foreach(min_a, min_b, mout, ROWS * COLS);
#else
  div_foreach(min_a, min_b, mout, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_abs(
    const MatrixCT<T, ROWS, COLS>& min, MatrixCT<T, ROWS, COLS>& mout) {
#ifdef ENABLE_ISPC
  ispc::abs_foreach(min, mout, ROWS * COLS);
#else
  abs_foreach(min, min_b, mout, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_sqrt(
    const MatrixCT<T, ROWS, COLS>& min, MatrixCT<T, ROWS, COLS>& mout) {
#ifdef ENABLE_ISPC
  ispc::sqrt_foreach(min, mout, ROWS * COLS);
#else
  sqrt_foreach(min, mout, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrix_transpose(
    const MatrixCT<T, ROWS, COLS>& min, MatrixCT<T, ROWS, COLS>& mout) {
#ifdef ENABLE_ISPC
  ispc::transpose(min, mout, ROWS, COLS);
#else
  transpose(min, mout, ROWS, COLS);
#endif
}

/* operators */

/* + */

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator+(
    const MatrixCT<T, ROWS, COLS>& lhs, const MatrixCT<T, ROWS, COLS>& rhs) {
  MatrixCT<T, ROWS, COLS> res;
  matrix_add(lhs, rhs, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator+(
    const MatrixCT<T, ROWS, COLS>& lhs, const T scalar) {
  MatrixCT<T, ROWS, COLS> res;
  matrix_add(lhs, res, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator+(
    const T scalar, const MatrixCT<T, ROWS, COLS>& rhs) {
  MatrixCT<T, ROWS, COLS> res;
  matrix_add(res, rhs, res);
  return res;
}

/* - */

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator-(
    const MatrixCT<T, ROWS, COLS>& lhs, const MatrixCT<T, ROWS, COLS>& rhs) {
  MatrixCT<T, ROWS, COLS> res;
  matrix_sub(lhs, rhs, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator-(
    const MatrixCT<T, ROWS, COLS>& lhs, const T scalar) {
  MatrixCT<T, ROWS, COLS> res;
  matrix_sub(lhs, res, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator-(
    const T scalar, const MatrixCT<T, ROWS, COLS>& rhs) {
  MatrixCT<T, ROWS, COLS> res;
  matrix_sub(res, rhs, res);
  return res;
}

/* * */

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator*(
    const MatrixCT<T, ROWS, COLS>& lhs, const MatrixCT<T, ROWS, COLS>& rhs) {
  MatrixCT<T, ROWS, COLS> res;
  matrix_mul(lhs, rhs, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator*(
    const MatrixCT<T, ROWS, COLS>& lhs, const T scalar) {
  MatrixCT<T, ROWS, COLS> res;
  matrix_mul(lhs, res, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator*(
    const T scalar, const MatrixCT<T, ROWS, COLS>& rhs) {
  MatrixCT<T, ROWS, COLS> res;
  matrix_mul(res, rhs, res);
  return res;
}

/* / */

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator/(
    const MatrixCT<T, ROWS, COLS>& lhs, const MatrixCT<T, ROWS, COLS>& rhs) {
  MatrixCT<T, ROWS, COLS> res;
  matrix_div(lhs, rhs, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator/(
    const MatrixCT<T, ROWS, COLS>& lhs, const T scalar) {
  MatrixCT<T, ROWS, COLS> res;
  matrix_div(lhs, res, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator/(
    const T scalar, const MatrixCT<T, ROWS, COLS>& rhs) {
  MatrixCT<T, ROWS, COLS> res;
  matrix_div(res, rhs, res);
  return res;
}

/* free functions */

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> abs(const MatrixCT<T, ROWS, COLS>& mat) {
  MatrixCT<T, ROWS, COLS> res;
  matrix_abs(mat, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> transpose(const MatrixCT<T, ROWS, COLS>& mat) {
  MatrixCT<T, COLS, ROWS> res;
  matrix_transpose(mat, res);
  return res;
}

/* stream */

template <typename T, size_t ROWS, size_t COLS>
std::istream& operator>>(std::istream& in, MatrixCT<T, ROWS, COLS>& mat) {
  for (size_t r = 0; r < ROWS; ++r) in >> mat[r];
  return in;
}

template <typename T, size_t ROWS, size_t COLS>
std::ostream& operator<<(std::ostream& out, MatrixCT<T, ROWS, COLS>& mat) {
  out << std::endl;
  for (size_t r = 0; r < ROWS; ++r) out << mat[r] << std::endl;
  return out;
}

template <typename T, size_t ROWS, size_t COLS>
std::ostream& operator<<(std::ostream& out, MatrixCT<T, ROWS, COLS>&& mat) {
  out << std::endl;
  for (size_t r = 0; r < ROWS; ++r) out << mat[r] << std::endl;
  return out;
}

}  // namespace kplge