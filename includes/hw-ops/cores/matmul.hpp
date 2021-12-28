/* Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "hw-ops/cores/mul.hpp"
#include "utils/load_matrix.hpp"

namespace ama {
namespace hw {
namespace core {

/**
 * @brief Matrix multiplication
 * It performs the multiplication of two matrices
 * @tparam T Data type
 * @tparam M Rows size of matrix a
 * @tparam N Columns size of matrix a
 * @param a Left Matrix to multiply
 * @param b Right Matrix to multiply
 * @param res Matrix with the result
 */
template <typename T, int M, int N>
void matmul(const T a[M][N], const T b[N][M], T res[M][M]) {
  constexpr int kDataWidth = T::width; /* Only supports ap_base datatypes */
#pragma HLS INTERFACE ap_fifo port = a
#pragma HLS INTERFACE ap_fifo port = b
#pragma HLS ARRAY_PARTITION variable = res complete dim = 0
  T a_buff[M][N];
#pragma HLS ARRAY_PARTITION variable = a_buff complete dim = 2
  T b_buff[N][M];
#pragma HLS ARRAY_PARTITION variable = b_buff complete dim = 1
  const bool cond = std::is_same<ap_int<kDataWidth>, T>::value;
  typename std::conditional<cond, ap_int<2 * kDataWidth>, T>::type mult_result;
  mult_result = 0;

  ama::utils::load_matrix<T, M, N>(a, a_buff);
  ama::utils::load_matrix<T, N, M>(b, b_buff);

Row:
  for (int i = 0; i < M; ++i) {
  Col:
    for (int j = 0; j < M; ++j) {
#pragma HLS PIPELINE
      mult_result = 0;
    Res:
      for (int k = 0; k < N; ++k) {
        decltype(mult_result) a_operand = a_buff[i][k],
                              b_operand = b_buff[k][j];
        if (cond) {
          decltype(mult_result) mult_element =
              ama::core::mul<decltype(mult_result)>(a_operand, b_operand);
          mult_element = mult_element.range(2 * kDataWidth - 2, kDataWidth - 1);
          mult_result += mult_element;
        } else {
          mult_result +=
              ama::core::mul<decltype(mult_result)>(a_operand, b_operand);
        }
      }
      res[i][j] = mult_result;
    }
  }
}

}  // namespace core
}  // namespace hw
}  // namespace ama
