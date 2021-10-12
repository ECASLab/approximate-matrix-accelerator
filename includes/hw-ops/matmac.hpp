/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "matadd.hpp"
#include "matmul.hpp"

namespace ama {
namespace hw {

/**
 * @brief Template Parameters
 * @param T Data type
 * @param M Rows size of matrix a
 * @param N Columns size of matrix a
 */
template <typename T, int M, int N>
/**
 * @brief Matrix multiplication-addition
 * It performs the multiplication and the addition in two steps.
 * First the multiplication, and then, the addition
 * @param a Left Matrix to multiply
 * @param b Right Matrix to multiply
 * @param c Right Matrix to add
 * @param res Matrix with the result
 */
void matmac(const T a[M][N], const T b[N][M], const T c[M][M], T res[M][M]) {
/*
#pragma HLS ARRAY_RESHAPE variable=res complete dim=2
#pragma HLS ARRAY_RESHAPE variable=c complete dim=2
#pragma HLS ARRAY_RESHAPE variable=b complete dim=1
#pragma HLS ARRAY_RESHAPE variable=a complete dim=2
#pragma HLS INTERFACE ap_fifo port = a
#pragma HLS INTERFACE ap_fifo port = b
*/
  T res_tmp[M][M];
  matmul<T, M, N>(a, b, res_tmp);
  matadd<T, M, M>(c, res_tmp, res);
}
}  // namespace hw
}  // namespace ama
