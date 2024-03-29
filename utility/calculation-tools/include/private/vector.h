#pragma once
#include <cassert>
#include <cmath>

#include <array>
#include <iostream>
#include <initializer_list>
#include <iterator>

#include "utils.h"

namespace kplutl {
template <typename T, size_t N>
struct VectorCT {
  std::array<T, N> data{};

  VectorCT<T, N>() = default;
  VectorCT<T, N>(VectorCT<T, N>& vectorCT) = default;
  VectorCT<T, N>& operator=(VectorCT<T, N>& matrixCT) =
      default;
  VectorCT<T, N>(VectorCT<T, N>&& vectorCT) = default;
  VectorCT<T, N>& operator=(VectorCT<T, N>&& matrixCT) =
      default;
  VectorCT<T, N>(T value) {
    for (size_t i = 0; i < N; ++i) data[i] = value;
  }
  VectorCT<T, N>(std::initializer_list<const T> list) {
    assert(list.size() == N);
    size_t i = 0;
    for (auto value : list) data[i++] = value;
  }
  template <typename It>
  VectorCT<T, N>(It first, It last) {
    auto size = std::distance(first, last);
    assert(size == N);
    auto it = first;
    for (size_t i = 0; i < size; ++i) {
      data[i] = *it;
      ++it;
    }
  }
  template <typename S>
  explicit VectorCT<T, N>(const S* source) {
    for (size_t i = 0; i < N; ++i) data[i] = (T)source[i];
  }
  template <typename S>
  explicit VectorCT<T, N>(const VectorCT<S, N>& source) {
    for (size_t i = 0; i < N; ++i) data[i] = (T)source[i];
  }

  T& operator[](size_t index) { return data[index]; }

  operator T*() { return reinterpret_cast<T*>(this); };

  operator const T*() const { return reinterpret_cast<const T*>(this); }

  VectorCT<T, N>& operator+=(const VectorCT<T, N>& lhs) {
    *this = *this + lhs;
    return *this;
  }

  VectorCT<T, N>& operator+=(const T scalar) {
    *this = *this + scalar;
    return *this;
  }

  VectorCT<T, N>& operator-=(const VectorCT<T, N>& lhs) {
    *this = *this - lhs;
    return *this;
  }

  VectorCT<T, N>& operator-=(const T scalar) {
    *this = *this - scalar;
    return *this;
  }

  VectorCT<T, N>& operator*=(const VectorCT<T, N>& lhs) {
    *this = *this * lhs;
    return *this;
  }

  VectorCT<T, N>& operator*=(const T scalar) {
    *this = *this * scalar;
    return *this;
  }

  VectorCT<T, N>& operator/=(const VectorCT<T, N>& lhs) {
    *this = *this / lhs;
    return *this;
  }

  VectorCT<T, N>& operator/=(const T scalar) {
    *this = *this / scalar;
    return *this;
  }
};

/* type defines */

using Vector2f = VectorCT<float, 2>;
using Vector3f = VectorCT<float, 3>;
using Vector4f = VectorCT<float, 4>;

/* inline functions */

template <typename T, size_t N>
inline void vector_add(
    const VectorCT<T, N>& vin_a, const VectorCT<T, N>& vin_b,
    VectorCT<T, N>& vout) {
#ifdef ENABLE_ISPC
  ispc::add_foreach(vin_a, vin_b, vout, N);
#else
  add_foreach(vin_a, vin_b, vout, N);
#endif
}

template <typename T, size_t N>
inline void vector_sub(
    const VectorCT<T, N>& vin_a, const VectorCT<T, N>& vin_b,
    VectorCT<T, N>& vout) {
#ifdef ENABLE_ISPC
  ispc::sub_foreach(vin_a, vin_b, vout, N);
#else
  sub_foreach(vin_a, vin_b, vout, N);
#endif
}

template <typename T, size_t N>
inline void vector_mul(
    const VectorCT<T, N>& vin_a, const VectorCT<T, N>& vin_b,
    VectorCT<T, N>& vout) {
#ifdef ENABLE_ISPC
  ispc::mul_foreach(vin_a, vin_b, vout, N);
#else
  mul_foreach(vin_a, vin_b, vout, N);
#endif
}

template <typename T, size_t N>
inline void vector_div(
    const VectorCT<T, N>& vin_a, const VectorCT<T, N>& vin_b,
    VectorCT<T, N>& vout) {
#ifdef ENABLE_ISPC
  ispc::div_foreach(vin_a, vin_b, vout, N);
#else
  div_foreach(vin_a, vin_b, vout, N);
#endif
}

template <typename T, size_t N>
inline void vector_abs(const VectorCT<T, N>& vin, VectorCT<T, N>& vout) {
#ifdef ENABLE_ISPC
  ispc::abs_foreach(vin, vout, N);
#else
  abs_foreach(vin, vout, N);
#endif
}

template <typename T, size_t N>
inline void vector_sqrt(const VectorCT<T, N>& vin, VectorCT<T, N>& vout) {
#ifdef ENABLE_ISPC
  ispc::sqrt_foreach(vin, vout, N);
#else
  sqrt_foreach(vin, vout, N);
#endif
}

template <typename T>
inline void vector_cross(
    const VectorCT<T, 3>& vin_a, const VectorCT<T, 3>& vin_b,
    VectorCT<T, 3>& vout) {
#ifdef ENABLE_ISPC
  ispc::cross(vin_a, vin_b, vout);
#else
  cross(vin_a, vin_b, vout);
#endif
}

/* operators */

/* + */

template <typename T, size_t N>
VectorCT<T, N> operator+(const VectorCT<T, N>& lhs, const VectorCT<T, N>& rhs) {
  VectorCT<T, N> res;
  vector_add(lhs, rhs, res);
  return res;
}

template <typename T, size_t N>
VectorCT<T, N> operator+(const VectorCT<T, N>& lhs, const T scalar) {
  VectorCT<T, N> res(scalar);
  vector_add(lhs, res, res);
  return res;
}

template <typename T, size_t N>
VectorCT<T, N> operator+(const T scalar, const VectorCT<T, N>& rhs) {
  VectorCT<T, N> res(scalar);
  vector_add(res, rhs, res);
  return res;
}

/* - */

template <typename T, size_t N>
VectorCT<T, N> operator-(const VectorCT<T, N>& lhs, const VectorCT<T, N>& rhs) {
  VectorCT<T, N> res;
  vector_sub(lhs, rhs, res);
  return res;
}

template <typename T, size_t N>
VectorCT<T, N> operator-(const VectorCT<T, N>& lhs, const T scalar) {
  VectorCT<T, N> res(scalar);
  vector_sub(lhs, res, res);
  return res;
}

template <typename T, size_t N>
VectorCT<T, N> operator-(const T scalar, const VectorCT<T, N>& rhs) {
  VectorCT<T, N> res(scalar);
  vector_sub(res, rhs, res);
  return res;
}

/* * */

template <typename T, size_t N>
VectorCT<T, N> operator*(const VectorCT<T, N>& lhs, const VectorCT<T, N>& rhs) {
  VectorCT<T, N> res;
  vector_mul(lhs, rhs, res);
  return res;
}

template <typename T, size_t N>
VectorCT<T, N> operator*(const VectorCT<T, N>& lhs, const T scalar) {
  VectorCT<T, N> res(scalar);
  vector_mul(lhs, res, res);
  return res;
}

template <typename T, size_t N>
VectorCT<T, N> operator*(const T scalar, const VectorCT<T, N>& rhs) {
  VectorCT<T, N> res(scalar);
  vector_mul(res, rhs, res);
  return res;
}

/* / */

template <typename T, size_t N>
VectorCT<T, N> operator/(const VectorCT<T, N>& lhs, const VectorCT<T, N>& rhs) {
  VectorCT<T, N> res;
  vector_div(lhs, rhs, res);
  return res;
}

template <typename T, size_t N>
VectorCT<T, N> operator/(const VectorCT<T, N>& lhs, const T scalar) {
  VectorCT<T, N> res(scalar);
  vector_div(lhs, res, res);
  return res;
}

template <typename T, size_t N>
VectorCT<T, N> operator/(const T scalar, const VectorCT<T, N>& rhs) {
  VectorCT<T, N> res(scalar);
  vector_div(res, rhs, res);
  return res;
}

/* free functions */

template <typename T, size_t N>
VectorCT<T, N> abs(const VectorCT<T, N>& vec) {
  VectorCT<T, N> res;
  vector_abs(vec, res);
  return res;
}

template <typename T, size_t N>
T dot(const VectorCT<T, N>& lhs, const VectorCT<T, N>& rhs) {
  VectorCT<T, N> tmp = lhs * rhs;
  T res = tmp[0];
  for (size_t i = 1; i < N; ++i) {
    res += tmp[i];
  }
  return res;
}

template <typename T>
T cross(const VectorCT<T, 2>& lhs, const VectorCT<T, 2>& rhs) {
  return lhs.v[0] * rhs.v[1] - lhs.v[1] * rhs.v[0];
}

template <typename T>
VectorCT<T, 3> cross(const VectorCT<T, 3>& lhs, const VectorCT<T, 3>& rhs) {
  VectorCT<T, 3> res;
  vector_cross(lhs, rhs, res);
  return res;
}

template <typename T, size_t N>
T length(const VectorCT<T, N>& vec) {
  return (T)std::sqrt(dot(vec, vec));
}

template <typename T, size_t N>
VectorCT<T, N> normalize(const VectorCT<T, N>& vec) {
  return vec / length(vec);
}

/* stream */

template <typename T, size_t N>
std::istream& operator>>(std::istream& in, VectorCT<T, N>& vec) {
  for (size_t i = 0; i < N; ++i) in >> vec.data[i];
  return in;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& out, const VectorCT<T, N>& vec) {
  out << "( ";
  for (size_t i = 0; i < N; ++i) out << vec.data[i] << (i != N - 1 ? ", " : "");
  out << " )";
  return out;
}

}  // namespace kplutl