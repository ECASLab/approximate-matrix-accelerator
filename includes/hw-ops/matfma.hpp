/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "cores/mul.hpp"
#include "utils/load_matrix.hpp"

namespace ama {
namespace hw {

/**
 * @brief Fused Multiply-Add
 * It performs the multiplication and the addition in one step.
 * @tparam T Data type
 * @tparam M Rows size of matrix a
 * @tparam N Columns size of matrix a
 * @param a Left Matrix to multiply
 * @param b Right Matrix to multiply
 * @param c Right Matrix to add
 * @param res Matrix with the result
 */
template <typename T, int M, int N>
void matfma(const T a[M][N], const T b[N][M], const T c[M][M], T res[M][M]) {
#if USE_REG_UNROLLING
#pragma HLS INTERFACE register port=a
#pragma HLS ARRAY_PARTITION variable=a complete dim=0
#pragma HLS INTERFACE register port=b
#pragma HLS ARRAY_PARTITION variable=b complete dim=0
#pragma HLS INTERFACE register port=c
#pragma HLS ARRAY_PARTITION variable=c complete dim=0
#pragma HLS INTERFACE register port=res
#pragma HLS ARRAY_PARTITION variable=res complete dim=0
#else
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
  ama::utils::load_matrix<T, M, N>(a, a_buff);
  ama::utils::load_matrix<T, N, M>(b, b_buff);
  ama::utils::load_matrix<T, M, M>(c, c_buff);
#endif
  T tmp = 0;
Rows:
  for (int i = 0; i < M; ++i) {
#pragma HLS PIPELINE
  Cols:
    for (int j = 0; j < M; ++j) {
       #if USE_REG_UNROLLING
       tmp = c[i][j];
       #else
       tmp = c_buff[i][j];
       #endif
    Res:
      for (int k = 0; k < N; ++k) {
         #if USE_REG_UNROLLING
         tmp += ama::core::mul(a[i][k], b[k][j]);
         #else
         tmp += ama::core::mul(a_buff[i][k], b_buff[k][j]);
         #endif
      }
      res[i][j] = tmp;
    }
  }
}
}  // namespace hw
}  // namespace ama
