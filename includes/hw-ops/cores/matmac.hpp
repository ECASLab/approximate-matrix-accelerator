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
 * @brief Matrix multiplication-addition
 * It performs the multiplication and the addition in two steps.
 * First the multiplication, and then, the addition
 * @tparam T Data type
 * @tparam M Rows size of matrix a
 * @tparam N Columns size of matrix a
 * @param a Left Matrix to multiply
 * @param b Right Matrix to multiply
 * @param c Right Matrix to add
 * @param res Matrix with the result
 */
template <typename T, int M, int N>
void matmac(const T a[M][N], const T b[N][M], const T c[M][M], T res[M][M]) {
  T res_tmp[M][M];
  matmul<T, M, N>(a, b, res_tmp);
  matadd<T, M, M>(c, res_tmp, res);
}
}  // namespace hw
}  // namespace ama
