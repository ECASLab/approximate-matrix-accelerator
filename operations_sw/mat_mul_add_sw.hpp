#pragma once

#include <cmath>

#include "matadd_sw.hpp"
#include "matmul_sw.hpp"

template <typename T, int MAT_A_ROWS, int MAT_A_COLS, int MAT_B_ROWS,
          int MAT_B_COLS>

void mat_mul_add(const T a[MAT_A_ROWS][MAT_A_ROWS],
                 const T b[MAT_B_ROWS][MAT_B_COLS],
                 const T c[MAT_A_ROWS][MAT_B_COLS],
                 T res[MAT_A_ROWS][MAT_B_COLS]) {
  matmul<T, MAT_A_ROWS, MAT_A_COLS, MAT_A_ROWS, MAT_B_ROWS>(a, b, res);
  matrixadd<T,MAT_A_ROWS,MAT_A_COLS,MAT_B_ROWS,MAT_B_ROWS>(c,res,res);
}