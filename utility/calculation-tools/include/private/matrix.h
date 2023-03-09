#pragma once
#include <vcruntime.h>
#include <cassert>
#include <cmath>

#include <iostream>
#include <initializer_list>

#include "utils.h"
#include "vector.h"

namespace kplutl {
template <typename T, size_t ROWS, size_t COLS>
struct MatrixCT {
  VectorCT<T, COLS> data[ROWS];

  MatrixCT<T, ROWS, COLS>() = default;
  MatrixCT<T, ROWS, COLS>(MatrixCT<T, ROWS, COLS>& matrixCT) = default;
  MatrixCT<T, ROWS, COLS>& operator=(MatrixCT<T, ROWS, COLS>& matrixCT) =
      default;
  MatrixCT<T, ROWS, COLS>(MatrixCT<T, ROWS, COLS>&& matrixCT) = default;
  MatrixCT<T, ROWS, COLS>& operator=(MatrixCT<T, ROWS, COLS>&& matrixCT) =
      default;

  MatrixCT<T, ROWS, COLS>(T value) {
    for (size_t r = 0; r < ROWS; ++r) {
      for (size_t c = 0; c < COLS; ++c) {
        data[r][c] = value;
      }
    }
  }
  MatrixCT<T, ROWS, COLS>(
      std::initializer_list<std::initializer_list<const T>> list) {
    assert(list.size() == ROWS);
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
  template <typename It>
  MatrixCT<T, ROWS, COLS>(It first, It last) {
    auto size = std::distance(first, last);
    assert(size == ROWS * COLS);
    auto it = first;
    for (size_t r = 0; r < ROWS; ++r) {
      for (size_t c = 0; c < COLS; ++c) {
        data[r][c] = *it;
        ++it;
      }
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

  VectorCT<T, COLS>& operator[](int row_index) { return data[row_index]; }

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
    const MatrixCT<T, ROWS, COLS>& min, MatrixCT<T, COLS, ROWS>& mout) {
#ifdef ENABLE_ISPC
  ispc::transpose(min, mout, ROWS, COLS);
#else
  transpose(min, mout, ROWS, COLS);
#endif
}

template <typename T, size_t D>
inline void matrix_identity(MatrixCT<T, D, D>& min, const size_t n) {
#ifdef ENABLE_ISPC
  ispc::identity(min, n);
#else
  identity(min, n);
#endif
}

template <typename T>
inline void vertex_transform(const MatrixCT<T, 4, 4>& min, VectorCT<T, 4>& v) {
#ifdef ENABLE_ISPC
  ispc::transform(min, v);
#else
  transform(min, v);
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
MatrixCT<T, COLS, ROWS> transpose(const MatrixCT<T, ROWS, COLS>& mat) {
  MatrixCT<T, COLS, ROWS> res;
  matrix_transpose(mat, res);
  return res;
}

template <typename T, size_t Da, size_t Db, size_t Dc>
MatrixCT<T, Da, Dc> multiply(
    const MatrixCT<T, Da, Db>& lhs, const MatrixCT<T, Db, Dc>& rhs) {
  MatrixCT<T, Da, Dc> res;
  MatrixCT<T, Dc, Db> rhs_t{transpose(rhs)};
  for (size_t r = 0; r < Da; ++r) {
    for (size_t c = 0; c < Dc; ++c) {
      res.data[r][c] = dot(lhs.data[r], rhs_t.data[c]);
    }
  }
  return res;
}

template <typename T, size_t D>
void identity(MatrixCT<T, D, D>& mat) {
  matrix_identity(mat, D);
}

template <typename T>
VectorCT<T, 4> transform(
    const MatrixCT<T, 4, 4>& min, const VectorCT<T, 4>& v) {
  VectorCT<T, 4> res{v};
  vertex_transform(min, res);
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

}  // namespace kplutl