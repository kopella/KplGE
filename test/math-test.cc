#include <vcruntime_typeinfo.h>
#include "kpl-math.h"
#include <iostream>

#include "matrix.h"
#include "vector.h"

using namespace kplge;

int main() {
  Vector3f vec_0(-1);
  Vector3f vec_1{1, 2, 3};

  float vec_fp[3]{4, 5, 6};
  Vector3f vec_2{vec_fp};

  Vector3f vec_3{Vector3f{7, 8, 9}};

  std::cout << "vec_0: " << vec_0 << std::endl;
  std::cout << "vec_1: " << vec_1 << std::endl;
  std::cout << "vec_2: " << vec_2 << std::endl;
  std::cout << "vec_3: " << vec_3 << std::endl;

  std::cout << "vec_1 + vec_2: " << vec_1 + vec_2 << std::endl;
  std::cout << "vec_1 - vec_2: " << vec_1 - vec_2 << std::endl;
  std::cout << "vec_1 * vec_2: " << vec_1 * vec_2 << std::endl;
  std::cout << "vec_1 / vec_2: " << vec_1 / vec_2 << std::endl;

  std::cout << "abs(vec_0): " << abs(vec_0) << std::endl;
  std::cout << "dot(vec_1, vec_2): " << dot(vec_1, vec_2) << std::endl;
  std::cout << "dot(vec_1, vec_3): " << dot(vec_1, vec_3) << std::endl;
  std::cout << "cross(vec_1, vec_2): " << cross(vec_1, vec_2) << std::endl;
  std::cout << "cross(vec_1, vec_3): " << cross(vec_1, vec_3) << std::endl;

  Matrix3X3f mat_0(-1);
  Matrix3X3f mat_1{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  float mat_fp[3][3]{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
  Matrix3X3f mat_2(mat_fp);

  std::cout << "mat_0: " << mat_0;
  std::cout << "mat_1: " << mat_1;
  std::cout << "mat_2: " << mat_2;

  std::cout << "mat_1 + mat_2: " << mat_1 + mat_2;
  std::cout << "mat_1 - mat_2: " << mat_1 - mat_2;
  std::cout << "mat_1 * mat_2: " << mat_1 * mat_2;
  std::cout << "mat_1 / mat_2: " << mat_1 / mat_2;

  std::cout << "abs(mat_0): " << abs(mat_0);
  std::cout << "transpose(mat_1):" << transpose(mat_1);
}