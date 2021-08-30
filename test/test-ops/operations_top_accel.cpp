/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "operations_top_accel.hpp"
#include "/home/eduardo/approximate-vector-accelerator/includes/hw-ops/mataccum_accel.hpp"
#include "/home/eduardo/approximate-vector-accelerator/includes/hw-ops/matadd_accel.hpp"
#include "/home/eduardo/approximate-vector-accelerator/includes/hw-ops/matmul_accel.hpp"

/**
 * @brief Matrix multiplication test
 * It calls the functions to perform
 * depending on the selection
 * @param selection Sorting
 * @param a Matrix of MxN dimensions
 * @param b Matrix of MxN dimensions
 * @param c Matrix of MxN dimensions
 * @param res Matrix with the result
 */
void operations_top_accel(int selection, const float a[kRows][kCols],
                          const float b[kRows][kCols],
                          const float c[kRows][kCols],
                          float res[kRows][kCols]) {
  switch (selection) {
    case 0:
      matadd<float, kRows, kCols>(a, b, res);
      break;
    case 1:
      matmul<float, kRows, kCols>(a, b, res);
      break;
    case 2:
      mat_mul_add<float, kRows, kCols>(a, b, c, res);
      break;
  }
}
