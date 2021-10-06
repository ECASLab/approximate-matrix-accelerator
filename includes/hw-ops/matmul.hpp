/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

namespace ama {
namespace hw {

template <typename T>
/**
 * @brief Multiplication of two numbers
 * @param a Left parameter to multiply
 * @param b Right parameter to multiply
 */
static T mul(const T a, const T b) {
#pragma HLS INLINE off
	return a * b;
}

template <typename T, int M, int N>
/**
 * @brief Matrix multiplication
 * It performs the multiplication of two matrices
 * @param a Left Matrix to multiply
 * @param b Right Matrix to multiply
 * @param res Matrix with the result
 */
void matmul(const T a[M][N], const T b[N][M], T res[M][M]) {
	T tmp = 0;
  Row: for (int i = 0; i < M; i++) {
    Col: for (int j = 0; j < M; j++) {
#pragma HLS PIPELINE
      tmp = 0;
      Res: for (int k = 0; k < N; k++) {
        tmp += mul(a[i][k], b[k][j]);
      }
      res[i][j] = tmp;
    }
  }
}
}  // namespace hw
}  // namespace ama
