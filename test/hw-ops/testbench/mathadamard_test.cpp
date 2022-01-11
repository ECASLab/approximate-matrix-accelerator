/*
 * Copyright 2022
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 * Based on the work by: Eduardo Salazar Villalobos
 * <eduarsalazar@estudiantec.cr>
 */

#include <ctime>
#include <iostream>

#include "linear.hpp"
#include "mathadamard_top_accel.hpp"
#include "utils/measure.hpp"

int main(int argc, char **argv) {
  float in_mat_a[ROWS][COLS];
  float in_mat_b[ROWS][COLS];
  float sw_result[ROWS][COLS];
  ExactType hw_in_mat_a[ROWS][COLS];
  ExactType hw_in_mat_b[ROWS][COLS];
  ExactType hw_result[ROWS][COLS];
  int err_cnt = 0;
  const float limit_factor = float(1 << (WL - 1)) / float((1 << WL));
  ama::utils::StatsMeter meter{};

  /* Generate the matrices */
  srand(SEED);
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      /* Create the input matrices */
      in_mat_a[i][j] = limit_factor * (float)std::rand() / (float)RAND_MAX;
      in_mat_b[i][j] = limit_factor * (float)std::rand() / (float)RAND_MAX;
      in_mat_a[i][j] *= (j % 2 == 0 ? -1 : 1);
      in_mat_b[i][j] *= (j % 3 == 0 ? -1 : 1);
      /* Copy to the hardware types */
      hw_in_mat_a[i][j] = in_mat_a[i][j];
      hw_in_mat_b[i][j] = in_mat_b[i][j];
      /* Compute the SW result */
      sw_result[i][j] = in_mat_a[i][j] * in_mat_b[i][j];
    }
  }

  /* Execute accel */
  mathadamard_top_accel(hw_in_mat_a, hw_in_mat_b, hw_result);

  float hw_result_f[ROWS][ROWS];
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < ROWS; ++j) {
      hw_result_f[i][j] = static_cast<float>(hw_result[i][j]);
      meter.Register(sw_result[i][j], hw_result_f[i][j], 2.f);
    }
  }
  ama::utils::compare_results<float, ROWS, ROWS>(hw_result_f, sw_result,
                                                 err_cnt, 0.05);
}
