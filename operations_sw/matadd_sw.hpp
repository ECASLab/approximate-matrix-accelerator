#pragma once

#include <cmath>

template <typename T, int MAT_A_ROWS, int MAT_A_COLS, int MAT_B_ROWS,
          int MAT_B_COLS>

void matrixadd(const T a[MAT_A_ROWS][MAT_A_COLS], const T b[MAT_B_ROWS][MAT_B_COLS],
               T res[MAT_A_ROWS][MAT_B_COLS]){
  if ((MAT_A_ROWS != MAT_B_ROWS) || (MAT_A_COLS != MAT_B_COLS)) return;

  for (int i = 0; i < MAT_A_ROWS; i++)
    for (int j = 0; j < MAT_B_COLS; j++) res[i][j] = a[i][j] + b[i][j];
}
