/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <iostream>

namespace ama {
namespace utils {

/**
 * @brief Prints a matrix
 * @tparam T Data type
 * @tparam M Rows size of matrix
 * @tparam N Cols size of matrix
 * @param hw_result A result matrix produced in
 * the hardware implementation to be printed
 * @param sw_result A result matrix produced in
 * the software implementation
 */
template <typename T, int M, int N>
void print_matrices(const T result[M][N]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      std::cout << result[i][j] << ' ';
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
}  // namespace utils
}  // namespace ama
