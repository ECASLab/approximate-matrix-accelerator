/* Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <ap_int.h>
#include <typeinfo>

#include "cores/mul.hpp"
#include "utils/load_matrix.hpp"
//#include "../../test/hw-ops/tops/testbench.hpp"

//#define WL 8

namespace ama {
namespace hw {

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
  typename std::conditional<cond, ap_int<2 * kDataWidth>, T>::type tmp;
  tmp = 0;

  ama::utils::load_matrix<T, M, N>(a, a_buff);
  ama::utils::load_matrix<T, N, M>(b, b_buff);

Row:
  for (int i = 0; i < M; ++i) {
  Col:
    for (int j = 0; j < M; ++j) {
#pragma HLS PIPELINE
      tmp = 0;
    Res:
      for (int k = 0; k < N; ++k) {
        //std::cout<<b_buff[i][k]<<std::endl;
        decltype(tmp) a__ = a_buff[i][k], b__ = b_buff[k][j];
        decltype(tmp) tmp2 = ama::core::mul(a__, b__);
        //std::cout<<a_buff[i][k] << " " << b_buff[k][j] << " " << tmp2 << std::endl;
        tmp2 = tmp2.range(2 * kDataWidth - 2, kDataWidth - 1);
        tmp += tmp2;
        
        //std::cout<<tmp<<std::endl;
      }
      if (cond) {
        std::cout<<tmp<<std::endl;
        //std::cout<<tmp.range(kDataWidth, 0)<<std::endl;
        res[i][j] = tmp;
        //std::cout<<res[i][j]<<std::endl;
      } else {
        res[i][j] = tmp;
      }
    }
  }
}
}  // namespace hw
}  // namespace ama
