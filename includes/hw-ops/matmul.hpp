/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

namespace ama {
namespace hw {

template <typename T, int M, int N>
/**
 * @brief Matrix multiplication
 * It performs the multiplication of two matrices
 * @param a Left Matrix to multiply
 * @param b Right Matrix to multiply
 * @param res Matrix with the result
 */
void matmul(const T a[M][N], const T b[M][N], T res[M][N]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      res[i][j] = 0;
      for (int k = 0; k < M; k++) {
        res[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}
};
};
