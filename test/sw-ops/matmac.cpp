/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <ctime>
#include <iostream>
#include <stdlib.h>

#include "linear.hpp"
#include "testbench.hpp"

int main() {
  ExactType a[kRows][kCols];
  ExactType b[kCols][kRows];
  ExactType c[kRows][kRows];
  ExactType res[kRows][kRows];

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
