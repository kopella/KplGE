#pragma once
#include <array>
#include <istream>
#include <initializer_list>

#include "kpl-math.h"

namespace kplge {
template <typename T, size_t N>
struct VectorMC {  // Vector for mathematical calculations
  std::array<T, N> data{};

  VectorMC<T, N>() {}
  VectorMC<T, N>(T value) {
    for (size_t i = 0; i < N; ++i) data[i] = value;
  }
  VectorMC<T, N>(std::initializer_list<const T> list) : VectorMC() {
    assert(list.size() == N);
    size_t i = 0;
    for (auto value : list) data[i++] = value;
  }
  template <typename S>
  explicit VectorMC<T, N>(const S* source) {
    for (size_t i = 0; i < N; ++i) data[i] = (T)source[i];
  }
  template <typename S>
  explicit VectorMC<T, N>(const VectorMC<S, N>& source) {
    for (size_t i = 0; i < N; ++i) data[i] = (T)source[i];
  }

  operator T*() { return reinterpret_cast<T*>(this); };
  operator const T*() const { return reinterpret_cast<const T*>(this); }

  VectorMC<T, N>& operator+=(const VectorMC<T, N>& lhs) {
    *this = *this + lhs;
    return *this;
  }

  VectorMC<T, N>& operator-=(const VectorMC<T, N>& lhs) {
    *this = *this - lhs;
    return *this;
  }

  VectorMC<T, N>& operator*=(const VectorMC<T, N>& lhs) {
    *this = *this * lhs;
    return *this;
  }

  VectorMC<T, N>& operator/=(const VectorMC<T, N>& lhs) {
    *this = *this / lhs;
    return *this;
  }

  VectorMC<T, N>& operator/=(const T scalar) {
    *this = *this / scalar;
    return *this;
  }
};

/* operators */

/* + */

template <typename T, size_t N>
inline void vector_add(
    const VectorMC<T, N>& vin_a, const VectorMC<T, N>& vin_b,
    VectorMC<T, N>& vout) {
#ifdef ENABLE_ISPC
  ispc::add_foreach(vin_a, vin_b, vout, N);
#else
  kplge::add_foreach(vin_a, vin_b, vout, N);
#endif
}

template <typename T, size_t N>
VectorMC<T, N> operator+(const VectorMC<T, N> lhs, const VectorMC<T, N> rhs) {
  VectorMC<T, N> res;
  vector_add(lhs, rhs, res);
  return res;
}

template <typename T, size_t N>
VectorMC<T, N> operator+(const VectorMC<T, N> lhs, const T scalar) {
  VectorMC<T, N> res(scalar);
  vector_add(lhs, res, res);
  return res;
}

template <typename T, size_t N>
VectorMC<T, N> operator+(const T scalar, const VectorMC<T, N> rhs) {
  VectorMC<T, N> res(scalar);
  vector_add(res, rhs, res);
  return res;
}

/* - */

template <typename T, size_t N>
inline void vector_sub(
    const VectorMC<T, N>& vin_a, const VectorMC<T, N>& vin_b,
    VectorMC<T, N>& vout) {
#ifdef ENABLE_ISPC
  ispc::sub_foreach(vin_a, vin_b, vout, N);
#else
  kplge::sub_foreach(vin_a, vin_b, vout, N);
#endif
}

template <typename T, size_t N>
VectorMC<T, N> operator-(const VectorMC<T, N> lhs, const VectorMC<T, N> rhs) {
  VectorMC<T, N> res;
  vector_sub(lhs, rhs, res);
  return res;
}

template <typename T, size_t N>
VectorMC<T, N> operator-(const VectorMC<T, N> lhs, const T scalar) {
  VectorMC<T, N> res(scalar);
  vector_sub(lhs, res, res);
  return res;
}

template <typename T, size_t N>
VectorMC<T, N> operator-(const T scalar, const VectorMC<T, N> rhs) {
  VectorMC<T, N> res(scalar);
  vector_sub(res, rhs, res);
  return res;
}

/* * */

template <typename T, size_t N>
inline void vector_mul(
    const VectorMC<T, N>& vin_a, const VectorMC<T, N>& vin_b,
    VectorMC<T, N>& vout) {
#ifdef ENABLE_ISPC
  ispc::mul_foreach(vin_a, vin_b, vout, N);
#else
  kplge::mul_foreach(vin_a, vin_b, vout, N);
#endif
}

template <typename T, size_t N>
VectorMC<T, N> operator*(const VectorMC<T, N> lhs, const VectorMC<T, N> rhs) {
  VectorMC<T, N> res;
  vector_mul(lhs, rhs, res);
  return res;
}

template <typename T, size_t N>
VectorMC<T, N> operator*(const VectorMC<T, N> lhs, const T scalar) {
  VectorMC<T, N> res(scalar);
  vector_mul(lhs, res, res);
  return res;
}

template <typename T, size_t N>
VectorMC<T, N> operator*(const T scalar, const VectorMC<T, N> rhs) {
  VectorMC<T, N> res(scalar);
  vector_mul(res, rhs, res);
  return res;
}

/* / */

template <typename T, size_t N>
inline void vector_div(
    const VectorMC<T, N>& vin_a, const VectorMC<T, N>& vin_b,
    VectorMC<T, N>& vout) {
#ifdef ENABLE_ISPC
  ispc::div_foreach(vin_a, vin_b, vout, N);
#else
  kplge::div_foreach(vin_a, vin_b, vout, N);
#endif
}

template <typename T, size_t N>
VectorMC<T, N> operator/(const VectorMC<T, N> lhs, const VectorMC<T, N> rhs) {
  VectorMC<T, N> res;
  vector_div(lhs, rhs, res);
  return res;
}

template <typename T, size_t N>
VectorMC<T, N> operator/(const VectorMC<T, N> lhs, const T scalar) {
  VectorMC<T, N> res(scalar);
  vector_div(lhs, res, res);
  return res;
}

template <typename T, size_t N>
VectorMC<T, N> operator/(const T scalar, const VectorMC<T, N> rhs) {
  VectorMC<T, N> res(scalar);
  vector_div(res, rhs, res);
  return res;
}

/* free functions */

template <typename T, size_t N>
T dot(const VectorMC<T, N> lhs, const VectorMC<T, N> rhs) {
  T res = (T)0;
  VectorMC<T, N> tmp = lhs * rhs;
  for (size_t i = 0; i < N; ++i) {
    res += tmp[i];
  }
}

/* stream */

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& out, const VectorMC<T, N>& v) {
  out << v.v[0];
  for (size_t i = 1; i < N; ++i) out << ", " << v.v[i];
  return out;
}

template <typename T, size_t N>
std::istream& operator>>(std::istream& in, VectorMC<T, N>& v) {
  in >> v.v[0];
  for (size_t i = 1; i < N; ++i) in >> v.v[i];
  return in;
}

}  // namespace kplge