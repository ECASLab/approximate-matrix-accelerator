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
  float in_mat_a[ROWS][COLS];
  float in_mat_b[ROWS][COLS];
  float sw_result[ROWS][COLS];
  ExactType hw_in_mat_a[ROWS][COLS];
  ExactType hw_in_mat_b[ROWS][COLS];
  ExactType hw_result[ROWS][COLS];
  int err_cnt = 0;

  srand(SEED);
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      in_mat_a[i][j] = 0.5f * (float)std::rand() / (float)RAND_MAX;
      in_mat_b[i][j] = 0.5f * (float)std::rand() / (float)RAND_MAX;
      in_mat_a[i][j] *= (j % 2 == 0 ? -1 : 1);
      in_mat_b[i][j] *= (j % 3 == 0 ? -1 : 1);
      hw_in_mat_a[i][j] = in_mat_a[i][j];
      hw_in_mat_b[i][j] = in_mat_b[i][j];
    }
  }

  ama::sw::matadd<float, ROWS, COLS>(in_mat_a, in_mat_b, sw_result);
  matadd_top_accel(hw_in_mat_a, hw_in_mat_b, hw_result);

  ama::utils::compare_results<ExactType, float, ROWS, COLS>(
      hw_result, sw_result, err_cnt, 0.05);
  ama::utils::print_matrices<ExactType, ROWS, COLS>(hw_result);
  ama::utils::print_matrices<float, ROWS, COLS>(sw_result);
}
