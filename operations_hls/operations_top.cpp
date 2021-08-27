#include <iostream>

#include "mat_mul_add.hpp"
#include "matadd.hpp"
#include "matmul.hpp"
#include "operations_top.hpp"

void operations_top(int selection, const float a[kRows][kCols],
                    const float b[kRows][kCols], const float c[kRows][kCols],
                    float res[kRows][kCols]) {
  switch (selection) {
    case 0:
      matrixadd<float, kRows, kCols, kRows, kCols>(a, b, res);
      break;
    case 1:
      matmul<float, kRows, kCols, kRows, kCols>(a, b, res);
      break;
    case 2:
      mat_mul_add<float, kRows, kCols, kRows, kCols>(a, b, c, res);
      break;
  }
}
