/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <iomanip>
#include <iostream>

namespace ama {
namespace utils {

/**
 * @brief Results test comparison
 * @tparam T Data type
 * @tparam M Rows size of matrices
 * @tparam N Cols size of matrices
 * @param hw_result Left Matrix to compare
 * It represents the result of hardware
 * implementation
 * @param sw_result Right Matrix to compare
 * It represents the result of software
 * implementation
 */
template <typename T, int M, int N>
void sign_changes(const T hw_result[M][N], const T sw_result[M][N]) {
  T tmp = 0;
  std::cout << std::setprecision(6) << std::fixed;
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      tmp = hw_result[i][j] * sw_result[i][j];
      if (tmp < 0) {
        std::cout << "Sign changes in indices " << '[' << i << ']' << '[' << j
                  << ']' << " hw_value " << hw_result[i][j] << ", "
                  << "sw_value " << sw_result[i][j] << std::endl;
      }
    }
  }
}
}
}
