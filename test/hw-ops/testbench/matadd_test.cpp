/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "linear.hpp"
#include "matadd_top_accel.hpp"

int main(int argc, char **argv) {
  float in_mat_a[kRows][kCols];
  float in_mat_b[kRows][kCols];
  float sw_result[kRows][kCols];
  ExactType hw_in_mat_a[kRows][kCols];
  ExactType hw_in_mat_b[kRows][kCols];
  ExactType hw_result[kRows][kCols];
  int err_cnt = 0;

  srand(kSeed);
  for (int i = 0; i < kRows; i++) {
    for (int j = 0; j < kCols; j++) {
      in_mat_a[i][j] = 0.5f * (float)std::rand() / (float)RAND_MAX;
      in_mat_b[i][j] = 0.5f * (float)std::rand() / (float)RAND_MAX;
      in_mat_a[i][j] *= (j % 2 == 0 ? -1 : 1);
      in_mat_b[i][j] *= (j % 3 == 0 ? -1 : 1);
      hw_in_mat_a[i][j] = in_mat_a[i][j];
      hw_in_mat_b[i][j] = in_mat_b[i][j];
    }
  }

  ama::sw::matadd<float, kRows, kCols>(in_mat_a, in_mat_b, sw_result);
  matadd_top_accel(hw_in_mat_a, hw_in_mat_b, hw_result);

  ama::utils::compare_results<ExactType, float,kRows, kCols>(hw_result, sw_result, err_cnt,
                                            0.05);
  ama::utils::print_matrices<ExactType, kRows, kCols>(hw_result);
  ama::utils::print_matrices<float, kRows, kCols>(sw_result);
}
