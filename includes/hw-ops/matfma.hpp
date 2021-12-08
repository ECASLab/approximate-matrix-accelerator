/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <ap_fixed.h>
#include <ap_int.h>

#include "cores/mul.hpp"
#include "utils/load_matrix.hpp"

namespace ama {
namespace hw {

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
#if USE_REG_UNROLLING
#pragma HLS INTERFACE register port = a
#pragma HLS ARRAY_PARTITION variable = a complete dim = 0
#pragma HLS INTERFACE register port = b
#pragma HLS ARRAY_PARTITION variable = b complete dim = 0
#pragma HLS INTERFACE register port = c
#pragma HLS ARRAY_PARTITION variable = c complete dim = 0
#pragma HLS INTERFACE register port = res
#pragma HLS ARRAY_PARTITION variable = res complete dim = 0
#else
#pragma HLS INTERFACE ap_fifo port = a
#pragma HLS INTERFACE ap_fifo port = b
#pragma HLS INTERFACE ap_fifo port = c
#pragma HLS INTERFACE ap_fifo port = res
#pragma HLS ARRAY_PARTITION variable = res complete dim = 2
  T a_buff[M][N];
#pragma HLS ARRAY_PARTITION variable = a_buff complete dim = 0
  T b_buff[N][M];
#pragma HLS ARRAY_PARTITION variable = b_buff complete dim = 0
  T c_buff[M][M];
#pragma HLS ARRAY_PARTITION variable = c_buff complete dim = 2
  ama::utils::load_matrix<T, M, N>(a, a_buff);
  ama::utils::load_matrix<T, N, M>(b, b_buff);
  ama::utils::load_matrix<T, M, M>(c, c_buff);
#endif
  constexpr int kDataWidth = T::width; /* Only supports ap_base datatypes */
  const bool cond = std::is_same<ap_int<kDataWidth>, T>::value;
  typename std::conditional<cond, ap_int<2 * kDataWidth>, T>::type mult_result;
  mult_result = 0;

#if DATATYPE == 0
  const ap_fixed<WL + 1, 1, AP_RND> alpha = 1.f / (2 * M); /* Transform factor to avoid overflow when working with ap_fixed */
#else
  const int alpha = (static_cast<int>(std::ceil(std::log2(M)) + 1)); /* Transform factor to avoid overflow when working with ap_int */
#endif

Rows:
  for (int i = 0; i < M; ++i) {
#pragma HLS PIPELINE
  Cols:
    for (int j = 0; j < M; ++j) {
#if USE_REG_UNROLLING
#define A_OPERAND a[i][k]
#define B_OPERAND b[k][j]
#define C_OPERAND c[i][j]
#else
#define A_OPERAND a_buff[i][k]
#define B_OPERAND b_buff[k][j]
#define C_OPERAND c_buff[i][j]
#endif

#if DATATYPE == 1
      mult_result = C_OPERAND >> alpha;
#else
      mult_result = C_OPERAND * alpha;
#endif
    Res:
      for (int k = 0; k < N; ++k) {
#if DATATYPE == 1
        decltype(mult_result) a_scaled = A_OPERAND >> alpha, b_scaled = B_OPERAND;
        decltype(mult_result) mult_element = ama::core::mul<decltype(mult_result)>(a_scaled, b_scaled);
        mult_element = mult_element.range(2 * kDataWidth - 2, kDataWidth - 1);
        mult_result += mult_element;
#else
        decltype(mult_result) a_scaled = A_OPERAND * alpha, b_scaled = B_OPERAND;
        mult_result += ama::core::mul<decltype(mult_result)>(a_scaled, b_scaled);
#endif
      }
      res[i][j] = mult_result;
    }
  }
}
}  // namespace hw
}  // namespace ama
