/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <cmath>
#include <iostream>

#if USE_HLS_MATH
#include <hls_math.h>
#define ABS(x) hls::abs(x)
#else
#define ABS(x) abs(x)
#endif

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
 * @param err_cnt accumulate the total amount of errors
 */
template <typename T, int M, int N>
void compare_results(const T hw_result[M][N], const T sw_result[M][N],
                     int &err_cnt, const float tolerance) {
  float relative_error = 0;
  float maxerr = 0;

  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (sw_result[i][j] != 0) {
        relative_error =
            ABS(hw_result[i][j] - sw_result[i][j]) / ABS(sw_result[i][j]);
      } else {
        relative_error = ABS(hw_result[i][j] - sw_result[i][j]) / 1.f;
      }
      if (relative_error > tolerance) {
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
