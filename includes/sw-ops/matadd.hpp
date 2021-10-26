/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

namespace ama {
namespace sw {

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
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      res[i][j] = a[i][j] + b[i][j];
    }
  }
}
}  // namespace sw
}  // namespace ama
