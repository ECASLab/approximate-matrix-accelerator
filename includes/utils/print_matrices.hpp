/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <iostream>
#include <iomanip>

namespace ama {
namespace utils {

/**
 * @brief Prints a matrix
 * @tparam T Data type
 * @tparam M Rows size of matrix
 * @tparam N Cols size of matrix
 * @param result A result matrix to be printed
 */
template <typename T, int M, int N>
void print_matrices(T result[M][N]) {
  std::cout << std::setprecision(6) << std::fixed;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      std::cout << static_cast<float>(result[i][j]) << ' ';
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
}  // namespace utils
}  // namespace ama
