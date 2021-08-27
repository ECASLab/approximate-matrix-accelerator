#include <iostream>

#include "mat_mul_add_sw.hpp"
#include "matadd_sw.hpp"
#include "matmul_sw.hpp"
#include "operations_top_sw.hpp"

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

int main() {
  const float a[3][3] = {{2.3, 4.5, 1.8}, {3.3, 0.7, 0.0}, {5.0, 6.8, 9.9}};

  const float b[3][3] = {{1.4, 8.2, 14.1}, {0.2, 1.4, 1.0}, {11.11, 6.3, 7.2}};

  const float c[3][3] = {{1.9, 6.7, 2.2}, {7.7, 8.8, 1.1}, {3.3, 4.4, 5.5}};

  float res[3][3];
  operations_top(2, a, b, c, res);
  std::cout << res[0][2] << std::endl;
  return 0;
}
