#include "kpl-math.h"
#include <iostream>

#include "vector.h"

using namespace kplge;

int main() {
  Vector3f vec_0(0);
  Vector3f vec_1{1, 2, 3};
  float fp[3]{4, 5, 6};
  Vector3f vec_2{fp};
  Vector3f vec_tmp{7, 8, 9};
  Vector3f vec_3{vec_tmp};

  std::cout << "vec_0: " << vec_0 << std::endl;
  std::cout << "vec_1: " << vec_1 << std::endl;
  std::cout << "vec_2: " << vec_2 << std::endl;
  std::cout << "vec_3: " << vec_3 << std::endl;

  std::cout << "vec_1 + vec_2: " << vec_1 + vec_2 << std::endl;
  std::cout << "vec_1 - vec_2: " << vec_1 - vec_2 << std::endl;
  std::cout << "vec_1 * vec_2: " << vec_1 * vec_2 << std::endl;
  std::cout << "vec_1 / vec_2: " << vec_1 / vec_2 << std::endl;

  std::cout << "dot(vec_1, vec_2): " << dot(vec_1, vec_2) << std::endl;
  std::cout << "dot(vec_1, vec_3): " << dot(vec_1, vec_3) << std::endl;
  std::cout << "cross(vec_1, vec_2): " << cross(vec_1, vec_2) << std::endl;
  std::cout << "cross(vec_1, vec_3): " << cross(vec_1, vec_3) << std::endl;

  std::cout << "abs(Vector3f{-2, 3, -4}): " << abs(Vector3f{-2, 3, -4})
            << std::endl;
}