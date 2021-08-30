/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "matadd_accel.hpp"
#include "matmul_accel.hpp"

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
void mat_mul_add(const T a[M][N],
                 const T b[M][N],
                 const T c[M][N],
                 T res[M][N]) {
  matmul<T, M, N>(a, b, res);
  matadd<T, M, N>(c, res, res);
}
