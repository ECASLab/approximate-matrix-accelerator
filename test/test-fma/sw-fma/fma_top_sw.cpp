/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <ctime>
#include <iostream>

#include "../../../includes/operations.hpp"

void fma_top_sw(const ExactType a[kRows][kCols], const ExactType b[kCols][kRows],
                const ExactType c[kRows][kRows], ExactType res[kRows][kRows]) {
  ama::sw::fma<ExactType, kRows, kCols>(a, b, c, res);
}

/**
 * @brief Prints a matrix
 * @param res print the result matrix
 */
void print_matrix(const ExactType res[kRows][kRows]) {
  for (int i = 0; i < kRows; i++) {
    for (int j = 0; j < kRows; j++) {
      std::cout << res[i][j] << ' ';
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
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
    }
    for (int k = 0; k < kRows; k++) {
      c[i][k] = 10 * (ExactType)rand() / (ExactType)RAND_MAX;
    }
  }
  float res[kRows][kRows];
  fma_top_sw(a, b, c, res);
  print_matrix(res);
  return 0;
}
