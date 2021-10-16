/* Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

template <typename T, int M, int N>

void load_matrix(const T fifo[M][N], T reg[M][N]){
#pragma HLS ARRAY_PARTITION variable=fifo complete dim=0
#pragma HLS INLINE off
#pragma HLS PIPELINE
  for(int i = 0; i < M; i++){
    for(int j = 0; j < N; j++){
      reg[i][j] = fifo[i][j];
    }
  }
}

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

/**
 * @brief Template Parameters
 * @param T Data type
 * @param M Rows size of matrix a
 * @param N Columns size of matrix a
 */
template <typename T, int M, int N>
/**
 * @brief Matrix multiplication
 * It performs the multiplication of two matrices
 * @param a Left Matrix to multiply
 * @param b Right Matrix to multiply
 * @param res Matrix with the result
 */
void matmul(const T a[M][N], const T b[N][M], T res[M][M]) {
//#pragma HLS ARRAY_RESHAPE variable = b complete dim = 1
//#pragma HLS ARRAY_RESHAPE variable = a complete dim = 2
//#pragma HLS ARRAY_RESHAPE variable = res complete dim = 0
#pragma HLS INTERFACE ap_fifo port = a
#pragma HLS INTERFACE ap_fifo port = b
#pragma HLS INTERFACE ap_fifo port = res
  T a_buff[M][N];
#pragma HLS ARRAY_PARTITION variable=a_buff complete dim=0
  //T a_row[M];
  T b_buff[N][M];
#pragma HLS ARRAY_PARTITION variable=b_buff complete dim=0
  T tmp = 0;

  load_matrix<T, M, N>(a,a_buff);
  load_matrix<T, N, M>(b,b_buff);
Row:
  for (int i = 0; i < M; i++) {
  Col:
    for (int j = 0; j < M; j++) {
#pragma HLS PIPELINE II=1
      //res_buff[i][j] = 0;
      tmp = 0;
      /*
      if (j == 0) {
      Cache_Row:
        for (int k = 0; k < M; k++) {
          a_row[k] = a_buff[i][k];
        }
      }

      if (i == 0) {
      Cache_Col:
        for (int k = 0; k < N; k++) {
          b_copy[k][j] = b_buff[k][j];
        }
      }
	*/
    Res:
      for (int k = 0; k < N; k++) {
    	 //res_buff[i][j] += mul(a_buff[i][k], b_buff[k][j]);
    	 tmp += mul(a_buff[i][k], b_buff[k][j]);
      }
      res[i][j] = tmp;
    }
  }
}
}  // namespace hw
}  // namespace ama

