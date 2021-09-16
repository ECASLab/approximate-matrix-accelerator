/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <ctime>
#include <iostream>

#include "../../../includes/sw-ops/matadd.hpp"
#include "../../../includes/sw-ops/matmac.hpp"
#include "../../../includes/sw-ops/matmul.hpp"
#include "../../../includes/sw-ops/operations_top_sw.hpp"

void operations_top_sw(int selection, const ExactType a[kRows][kCols],
                       const ExactType b[kCols][kRows],
                       const ExactType c[kRows][kRows],
                       ExactType res[kRows][kRows]) {
  switch (selection) {
    case 0:
      ama::sw::matadd<ExactType, kRows, kRows>(c, c, res);
      break;
    case 1:
      ama::sw::matmul<ExactType, kRows, kCols>(a, b, res);
      break;
    case 2:
      ama::sw::matmac<ExactType, kRows, kCols>(a, b, c, res);
      break;
  }
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

  ExactType res[kRows][kRows];
  operations_top_sw(2, a, b, c, res);
  print_matrix(res);
  return 0;
}
