/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

namespace ama {
namespace hw {

/**
 * @brief Template Parameters
 * @param T Data type
 * @param M Rows size of matrices
 * @param N Columns size of matrices
 */
template <typename T, int M, int N>
/**
 * @brief Matrix addition
 * It performs the addition of two matrices.
 * @param a Left Matrix to add
 * @param b Right Matrix to add
 * @param res Matrix with the result
 */
void matadd(const T a[M][N], const T b[M][N], T res[M][N]) {
#pragma HLS ARRAY_PARTITION variable = res complete dim = 0
#pragma HLS ARRAY_PARTITION variable = b complete dim = 0
#pragma HLS ARRAY_PARTITION variable = a complete dim = 0

#pragma HLS PIPELINE
Rows:
  for (int i = 0; i < M; i++) {
  Cols:
    for (int j = 0; j < N; j++) {
      res[i][j] = a[i][j] + b[i][j];
    }
  }
}
}  // namespace hw
}  // namespace ama
