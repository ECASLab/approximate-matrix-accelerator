/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <cmath>
#include <iostream>

#include <hls_math.h>

namespace ama {
namespace utils {

template <int M, int N, typename TS, typename TH>
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
void compare_results(const TH hw_result[M * N], const TS sw_result[M * N],
                     int &err_cnt, const float tolerance) {
  float relative_error = 0;
  float maxerr = 0;

  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      int index = i * N + j;
      if (sw_result[index] != 0) {
        relative_error =
            hls::abs((float)hw_result[index] - sw_result[index]) / sw_result[index];
      } else {
        relative_error = hls::abs((float)hw_result[index] - sw_result[index]) / 1.f;
      }
      if (relative_error > tolerance) {
        std::cout << relative_error << std::endl;
        std::cout << "It occurs a mismatches in indices " << '[' << i << ']'
                  << '[' << j << ']' << std::endl;
        err_cnt++;
      }
      maxerr = std::max(maxerr, relative_error);
    }
  }

  std::cout << "MaxErrorTh: " << maxerr << std::endl;
}
}  // namespace utils
}  // namespace ama
