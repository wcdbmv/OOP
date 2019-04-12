#ifndef TEST_H
#define TEST_H

#include <iostream>

#include "vector.h"

template <typename T>
void test(std::ostream& out, const Vector<T>& a, const Vector<T>& b, T c) {
  out << "Vector a: " << a << std::endl;
  out << "Vector b: " << b << std::endl;
  out << std::endl;

  out << "Vector a + b: " << a + b << std::endl;
  out << "Vector a - b: " << a - b << std::endl;
  out << "Scalar a * b: " << a * b << std::endl;
  out << "Vector a / " << c << ": " << a / c << std::endl;
  out << "Vector a * " << c << ": " << a * c << std::endl;
  out << "Vector b * " << c << ": " << b * c << std::endl;
}

#endif  // TEST_H
