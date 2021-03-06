/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <ctime>
#include <iostream>

#include "linear.hpp"
#include "matmac_top_accel.hpp"
#include "utils/measure.hpp"

int main(int argc, char **argv) {
  float in_mat_a[ROWS][COLS];
  float in_mat_b[COLS][ROWS];
  float in_mat_c[ROWS][ROWS];
  float sw_result[ROWS][ROWS];
  ExactType hw_in_mat_a[ROWS][COLS];
  ExactType hw_in_mat_b[COLS][ROWS];
  ExactType hw_in_mat_c[ROWS][ROWS];
  ExactType hw_result[ROWS][ROWS];
  int err_cnt = 0;
  const float alpha = 1.f / (2 * ROWS);
  const int inv_alpha = 2 * ROWS;
  const float limit_factor = float(((1ul << WL) - 1)) / float((1ul << WL));
  ama::utils::StatsMeter meter{};

  srand(SEED);
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      in_mat_a[i][j] = limit_factor * (float)std::rand() / (float)RAND_MAX;
      in_mat_b[j][i] = limit_factor * (float)std::rand() / (float)RAND_MAX;
      in_mat_a[i][j] *= (j % 2 == 0 ? -1 : 1);
      in_mat_b[j][i] *= (j % 3 == 0 ? -1 : 1);
#if DATATYPE == 0
      hw_in_mat_a[i][j] = in_mat_a[i][j] * alpha;
      hw_in_mat_b[j][i] = in_mat_b[j][i];
#else
      hw_in_mat_a[i][j] = in_mat_a[i][j] * alpha * (1ul << WL);
      hw_in_mat_b[j][i] = in_mat_b[j][i] * (1ul << WL);
#endif
    }
    for (int k = 0; k < ROWS; ++k) {
      in_mat_c[i][k] = limit_factor * (float)std::rand() / (float)RAND_MAX;
      in_mat_c[i][k] *= (k % 5 == 0 ? -1 : 1);
#if DATATYPE == 0
      hw_in_mat_c[i][k] = in_mat_c[i][k] * alpha;
#else
      hw_in_mat_c[i][k] = in_mat_c[i][k] * alpha * (1ul << WL);
#endif
    }
  }

  ama::sw::matmac<float, ROWS, COLS>(in_mat_a, in_mat_b, in_mat_c, sw_result);
  matmac_top_accel(hw_in_mat_a, hw_in_mat_b, hw_in_mat_c, hw_result);

#if DATATYPE == 0
  float scale = float(1ul);
#else
  float scale = float(1ul) / (float)(1ul << WL);
#endif

  float hw_result_f[ROWS][ROWS];
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < ROWS; ++j) {
      hw_result_f[i][j] =
          static_cast<float>(hw_result[i][j]) * scale * inv_alpha;
      if (sw_result[i][j] != 0) {
        meter.Register(sw_result[i][j], hw_result_f[i][j], sw_result[i][j]);
      } else {
        meter.Register(sw_result[i][j], hw_result_f[i][j], 1.f);
      }
    }
  }
  ama::utils::compare_results<float, ROWS, ROWS>(hw_result_f, sw_result,
                                                 err_cnt, 0.05);
  ama::utils::sign_changes<float, ROWS, ROWS>(hw_result_f, sw_result);
  ama::utils::print_matrices<float, ROWS, ROWS>(hw_result_f);
  ama::utils::print_matrices<float, ROWS, ROWS>(sw_result);
}
