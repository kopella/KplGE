#include <iostream>
#include <vector>

#include "kplcalct.h"
#include "private/vector.h"

using namespace kplutl;

int main() {
  Vector3f vec_0{};
  Vector3f vec_1{1, 2, 3};

  float vec_fp[3]{4, 5, 6};
  Vector3f vec_2{vec_fp};

  Vector3f vec_3{Vector3f{7, 8, 9}};

  std::vector<float> vec_vec{1, 4, 7};
  Vector3f vec_4{vec_vec.begin(), vec_vec.end()};

  std::cout << "vec_0: " << vec_0 << std::endl;
  std::cout << "vec_1: " << vec_1 << std::endl;
  std::cout << "vec_2: " << vec_2 << std::endl;
  std::cout << "vec_3: " << vec_3 << std::endl;
  std::cout << "vec_4: " << vec_4 << std::endl;

  std::cout << "vec_1 + vec_2: " << vec_1 + vec_2 << std::endl;
  std::cout << "vec_1 - vec_2: " << vec_1 - vec_2 << std::endl;
  std::cout << "vec_1 * vec_2: " << vec_1 * vec_2 << std::endl;
  std::cout << "vec_1 / vec_2: " << vec_1 / vec_2 << std::endl;

  std::cout << "abs(vec_0): " << abs(vec_0) << std::endl;
  std::cout << "dot(vec_1, vec_2): " << dot(vec_1, vec_2) << std::endl;
  std::cout << "dot(vec_1, vec_3): " << dot(vec_1, vec_3) << std::endl;
  std::cout << "cross(vec_1, vec_2): " << cross(vec_1, vec_2) << std::endl;
  std::cout << "cross(vec_1, vec_3): " << cross(vec_1, vec_3) << std::endl;

  Matrix3X3f mat_0{};
  Matrix3X3f mat_1{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  float mat_fp[3][3]{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
  Matrix3X3f mat_2{mat_fp};

  std::vector<float> mat_vec{1, 4, 7, 2, 5, 8, 3, 6, 9};
  Matrix3X3f mat_3{mat_vec.begin(), mat_vec.end()};

  std::cout << "mat_0: " << mat_0;
  std::cout << "mat_1: " << mat_1;
  std::cout << "mat_2: " << mat_2;
  std::cout << "mat_3: " << mat_3;

  std::cout << "mat_1 + mat_2: " << mat_1 + mat_2;
  std::cout << "mat_1 - mat_2: " << mat_1 - mat_2;
  std::cout << "mat_1 * mat_2: " << mat_1 * mat_2;
  std::cout << "mat_1 / mat_2: " << mat_1 / mat_2;

  std::cout << "abs(mat_0): " << abs(mat_0);
  std::cout << "transpose(mat_1):" << transpose(mat_1);
}