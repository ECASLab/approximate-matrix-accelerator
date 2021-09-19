/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <ctime>
#include <iostream>

#include "../../../includes/linear.hpp"

void matfma_top_sw(const ExactType a[kRows][kCols], const ExactType b[kCols][kRows],
                const ExactType c[kRows][kRows], ExactType res[kRows][kRows]) {
  ama::sw::matfma<ExactType, kRows, kCols>(a, b, c, res);
}

int main() {
  ExactType a[kRows][kCols];
  ExactType b[kCols][kRows];
  ExactType c[kRows][kRows];

  srand(time(nullptr));
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
  ExactType res[kRows][kRows];
  matfma_top_sw(a, b, c, res);
  ama::utils::print_matrices<ExactType,kRows,kRows>(res);
  return 0;
}
