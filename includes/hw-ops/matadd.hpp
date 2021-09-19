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
 * @brief Matrix addition
 * It performs the addition of two matrices.
 * @param a Left Matrix to add
 * @param b Right Matrix to add
 * @param res Matrix with the result
 */
void matadd(const T *a, const T *b, T *res) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      int index = i * N + j;
      res[index] = a[index] + b[index];
    }
  }
}
}  // namespace hw
}  // namespace ama
