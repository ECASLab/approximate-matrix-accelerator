/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

namespace ama {
namespace sw {
  
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
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < M; ++j) {
      res[i][j] = c[i][j];
      for (int k = 0; k < N; ++k) {
        res[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}
}  // namespace sw
}  // namespace ama
