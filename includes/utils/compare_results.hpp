/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <cmath>
#include <iostream>


#if USE_HLS_MATH == 1
#define HLS 1
#include <hls_math.h>
#else 
#define HLS 0
#endif


namespace ama {
namespace utils {

template <typename TH, typename TS, int M, int N>
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
void compare_results(const TH hw_result[M][N], const TS sw_result[M][N],
                     int &err_cnt, const float tolerance) {
  float relative_error = 0;
  float maxerr = 0;

  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (sw_result[i][j] != 0) {
        #if HLS == 1 
          relative_error =
              hls::abs((float)hw_result[i][j] - sw_result[i][j]) / sw_result[i][j];
              std::cout << "hola" << std::endl;
        #else
          relative_error =
              abs((float)hw_result[i][j] - sw_result[i][j]) / sw_result[i][j];
        #endif
      } else {
        #if HLS == 1
          relative_error = hls::abs((float)hw_result[i][j] - sw_result[i][j]) / 1.f;
          std::cout << "hola" << std::endl;
        #else
          relative_error = abs((float)hw_result[i][j] - sw_result[i][j]) / 1.f;
        #endif
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
