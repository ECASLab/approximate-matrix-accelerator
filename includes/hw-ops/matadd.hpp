/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <ap_fixed.h>

namespace ama {
namespace hw {

/**
 * @brief Matrix addition
 * It performs the addition of two matrices.
 * @tparam T Data type
 * @tparam M Rows size of matrices
 * @tparam N Columns size of matrices
 * @param a Left Matrix to add
 * @param b Right Matrix to add
 * @param res Matrix with the result
 */
template <typename T, int M, int N>
void matadd(const T a[M][N], const T b[M][N], T res[M][N]) {
#pragma HLS ARRAY_PARTITION variable = res complete dim = 0
#pragma HLS ARRAY_PARTITION variable = b complete dim = 0
#pragma HLS ARRAY_PARTITION variable = a complete dim = 0
  const ap_fixed<WL + 1, 1, AP_RND> alpha = 1.f / M; /* Transform factor to avoid overflow */

#pragma HLS PIPELINE
Rows:
  for (int i = 0; i < M; ++i) {
  Cols:
    for (int j = 0; j < N; ++j) {
      res[i][j] = (a[i][j] * alpha + b[i][j]) * 1 / 2;
    }
  }
}
}  // namespace hw
}  // namespace ama
