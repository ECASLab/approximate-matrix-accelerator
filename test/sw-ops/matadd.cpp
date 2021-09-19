/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <ctime>
#include <iostream>

#include "linear.hpp"
#include "testbench.hpp"

int main() {
  ExactType a[kRows][kCols];
  ExactType b[kRows][kCols];
  ExactType res[kRows][kCols];

  for (int i = 0; i < kRows; i++) {
    for (int j = 0; j < kCols; j++) {
      a[i][j] = 10 * (ExactType)rand() / (ExactType)RAND_MAX;
      b[i][j] = 10 * (ExactType)rand() / (ExactType)RAND_MAX;
      a[i][j] *= j % 2 ? -1 : 1;
      b[i][j] *= j % 3 ? -1 : 1;
    }
  }

  ama::sw::matadd<ExactType, kRows, kCols>(a, b, res);
  ama::utils::print_matrices<ExactType, kRows, kCols>(res);
}
