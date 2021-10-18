/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "load_matrix.hpp"
#include "mul.hpp"

namespace ama {
namespace hw {

/**
 * @brief Template Parameters
 * @param T Data type
 * @param M Rows size of matrix a
 * @param N Columns size of matrix a
 */
template <typename T, int M, int N>
/**
 * @brief Fused Multiply-Add
 * It performs the multiplication and the addition in one step.
 * @param a Left Matrix to multiply
 * @param b Right Matrix to multiply
 * @param c Right Matrix to add
 * @param res Matrix with the result
 */
void matfma(const T a[M][N], const T b[N][M], const T c[M][M], T res[M][M]) {
// Uncomment the following section for not
// register parallelism scenario (scenario 1)
#pragma HLS INTERFACE ap_fifo port = a
#pragma HLS INTERFACE ap_fifo port = b
#pragma HLS INTERFACE ap_fifo port = c
#pragma HLS INTERFACE ap_fifo port = res
#pragma HLS ARRAY_PARTITION variable = res complete dim = 2
  T a_buff[M][N];
#pragma HLS ARRAY_PARTITION variable = a_buff complete dim = 0
  T b_buff[N][M];
#pragma HLS ARRAY_PARTITION variable = b_buff complete dim = 0
  T c_buff[M][M];
#pragma HLS ARRAY_PARTITION variable = c_buff complete dim = 2

  load_matrix<T, M, N>(a, a_buff);
  load_matrix<T, N, M>(b, b_buff);
  load_matrix<T, M, M>(c, c_buff);

// Uncomment the following section for scenario complete
// register parallelism scenario (scenario 2)
/*
#pragma HLS INTERFACE register port=a
#pragma HLS ARRAY_PARTITION variable=a complete dim=0
#pragma HLS INTERFACE register port=b
#pragma HLS ARRAY_PARTITION variable=b complete dim=0
#pragma HLS INTERFACE register port=c
#pragma HLS ARRAY_PARTITION variable=c complete dim=0
#pragma HLS INTERFACE register port=res
#pragma HLS ARRAY_PARTITION variable=res complete dim=0
*/
  T tmp = 0;
Rows:
  for (int i = 0; i < M; i++) {
#pragma HLS PIPELINE
  Cols:
    for (int j = 0; j < M; j++) {
// Uncommnt following line for scenario 2
//#pragma HLS PIPELINE
      tmp = c_buff[i][j];
    // Uncommnt following line for scenario 2
    // tmp = c[i][j];
    Res:
      for (int k = 0; k < N; k++) {
        tmp += mul(a_buff[i][k], b_buff[k][j]);
        // Uncommnt following line for scenario 2
        // tmp += mulfma(a[i][k], b[k][j]);
      }
      res[i][j] = tmp;
    }
  }
}
}  // namespace hw
}  // namespace ama
