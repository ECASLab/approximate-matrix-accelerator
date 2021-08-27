#pragma once 

#include <cmath>

template <typename T, int MAT_A_ROWS, int MAT_A_COLS, int MAT_B_ROWS,
          int MAT_B_COLS>

void matmul(const T a[MAT_A_ROWS][MAT_A_COLS], const T b[MAT_B_ROWS][MAT_B_COLS],
            T res[MAT_A_ROWS][MAT_B_COLS]){
    for(int i = 0; i < MAT_A_ROWS; i++){
        for(int j = 0; j < MAT_B_COLS; j++){
            res[i][j] = 0;
            for(int k = 0; k < MAT_B_ROWS; k++){
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}
