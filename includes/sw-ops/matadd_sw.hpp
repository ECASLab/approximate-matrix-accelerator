/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

template <typename T, int M, int N>
/**
 * @brief Matrix addition
 * It performs the addition of two matrices.
 * @param a Left Matrix to add 
 * @param b Right Matrix to add
 * @param res Matrix with the result
 */
void matadd(const T a[M][N],
               const T b[N][N],
               T res[M][N]) {
  for (int i = 0; i < M; i++){
    for (int j = 0; j < N; j++){ 
      res[i][j] = a[i][j] + b[i][j];
    }
  }
}
