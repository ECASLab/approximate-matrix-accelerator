/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

namespace ama {
namespace utils {

/**
 * @brief Load_Matrix
 * It loads the input matrix to a local matrix.
 * @tparam T Data type
 * @tparam M Rows size of matrices
 * @tparam N Columns size of matrices
 * @param fifo Matrix with fifo pragma
 * @param reg  Local matrix
 */
template <typename T, int M, int N>
void load_matrix(const T fifo[M][N], T reg[M][N]) {
#pragma HLS INLINE off
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      reg[i][j] = fifo[i][j];
    }
  }
}
}
}
