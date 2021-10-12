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
 * @brief Multiply
 * @param a Left parameter to multiply
 * @param b Right parameter to multiply
 */
static T mulfma(const T a, const T b) {
#pragma HLS INLINE off
  return a * b;
}

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
  // T a_row[M];
  // T b_copy[N][M];
  T tmp = 0;
Rows:
  for (int i = 0; i < M; i++) {
#pragma HLS PIPELINE
  Cols:
    for (int j = 0; j < M; j++) {
      //#pragma HLS PIPELINE
      tmp = c[i][j];
    /*
          if (j == 0){
              Cache_Row: for(int k = 0; k < M; k++){
                      a_row[k] = a[i][k];
              }
          }

          if(i == 0){
              Cache_Col: for(int k = 0; k < N; k++){
                      b_copy[k][j] = b[k][j];
              }
          }
    */
    Res:
      for (int k = 0; k < N; k++) {
        tmp += mulfma(a[i][k], b[k][j]);
      }
      res[i][j] = tmp;
    }
  }
}
}  // namespace hw
}  // namespace ama
