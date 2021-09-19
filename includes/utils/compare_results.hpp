/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <iostream>

namespace ama {
namespace utils {

template <typename T, int M, int N>
/**
 * @brief Results test comparison
 * @param hw_result Left Matrix to compare
 * It represents the result of hardware
 * implementation
 * @param sw_result Right Matrix to compare
 * It represents the result of software
 * implementation
 * @param err_cnt accumulate the total amount of errors
 */
void compare_results(const T hw_result[M][M], const T sw_result[M][M],
                     int &err_cnt, const T tolerance) {
  float relative_error = 0;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
      if (sw_result[i][j] != 0) {
        relative_error =
            abs(hw_result[i][j] - sw_result[i][j]) / sw_result[i][j];
      } else {
        relative_error = abs(hw_result[i][j] - sw_result[i][j]) / float{1.f};
      }
      if (relative_error > tolerance) {
        std::cout << relative_error << std::endl;
        std::cout << "It occurs a mismatches in indices " << '[' << i << ']'
                  << '[' << j << ']' << std::endl;
        err_cnt++;
      }
    }
  }
}
}  // namespace utils
}  // namespace ama
