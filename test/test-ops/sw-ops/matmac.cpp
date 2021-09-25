#include <iostream>

#include "../../../includes/linear.hpp"

#ifndef kRows
#define kRows 12
#endif

#ifndef kCols
#define kCols 12
#endif

int main() {
  ExactType a[kRows][kCols];
  ExactType b[kRows][kCols];
  ExactType c[kRows][kCols];
  ExactType res[kRows][kCols];

  for (int i = 0; i < kRows; i++) {
    for (int j = 0; j < kCols; j++) {
      a[i][j] = 10 * (ExactType)rand() / (ExactType)RAND_MAX;
      b[j][i] = 10 * (ExactType)rand() / (ExactType)RAND_MAX;
      a[i][j] *= j % 2 ? -1 : 1;
      b[j][i] *= j % 3 ? -1 : 1;
    }
    for (int k = 0; k < kRows; k++) {
      c[i][k] = 10 * (ExactType)rand() / (ExactType)RAND_MAX;
      c[i][k] *= k % 5 ? -1 : 1;
    }
  }

  ama::sw::matmac<ExactType, kRows, kCols>(a, b, c, res);
  ama::utils::print_matrices<ExactType, kRows, kCols>(res);
}