/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <cmath>
#include <ctime>
#include <iostream>

#include "linear.hpp"
#include "utils/measure.hpp"
#include "vecfma_top_accel.hpp"

#if DATATYPE != 0
#error Vectorise does not support integers
#endif

int main(int argc, char **argv) {
  float in_mat_a[ACCEL * ROWS][ROWS];
  float in_mat_b[ACCEL * ROWS][ROWS];
  float in_mat_c[ACCEL * ROWS][ROWS];
  float sw_result[ACCEL * ROWS][ROWS];
  ExactType hw_in_mat_a[ACCEL * ROWS][ROWS];
  ExactType hw_in_mat_b[ACCEL * ROWS][ROWS];
  ExactType hw_in_mat_c[ACCEL * ROWS][ROWS];
  ExactType hw_result[ACCEL * ROWS][ROWS];

  int err_cnt = 0;
  const float limit_factor = float(1ul << (WL - 1)) / float((1ul << WL));
  ama::utils::StatsMeter meter{};

  srand(SEED);
  for (int i = 0; i < (ACCEL * ROWS); ++i) {
    for (int j = 0; j < ROWS; ++j) {
      in_mat_a[i][j] = limit_factor * (float)std::rand() / (float)RAND_MAX;
      in_mat_b[i][j] = limit_factor * (float)std::rand() / (float)RAND_MAX;
      in_mat_c[i][j] = limit_factor * (float)std::rand() / (float)RAND_MAX;
      in_mat_a[i][j] *= (j % 2 == 0 ? -1 : 1);
      in_mat_b[i][j] *= (j % 3 == 0 ? -1 : 1);
      in_mat_c[i][j] *= (j % 5 == 0 ? -1 : 1);

      hw_in_mat_a[i][j] = in_mat_a[i][j];
      hw_in_mat_b[i][j] = in_mat_b[i][j];
      hw_in_mat_c[i][j] = in_mat_c[i][j];
    }
  }

  for (int k = 0; k < ACCEL; ++k) {
    ama::sw::matfma<float, ROWS, ROWS>(&in_mat_a[k * ROWS], &in_mat_b[k * ROWS],
                                       &in_mat_c[k * ROWS],
                                       &sw_result[k * ROWS]);
  }

  vecfma_top_accel(hw_in_mat_a, hw_in_mat_b, hw_in_mat_c, hw_result);

  float scale = float(1);
  const float inv_alpha = 2 * ROWS;

  float hw_result_f[ACCEL * ROWS][ROWS];
  for (int i = 0; i < (ACCEL * ROWS); ++i) {
    for (int j = 0; j < ROWS; ++j) {
      hw_result_f[i][j] =
          static_cast<float>(hw_result[i][j]) * scale * inv_alpha;
      meter.Register(sw_result[i][j], hw_result_f[i][j], 2.f);
    }
  }

  ama::utils::print_matrices<float, ACCEL * ROWS, ROWS>(hw_result_f);
  ama::utils::print_matrices<float, ACCEL * ROWS, ROWS>(sw_result);
}
