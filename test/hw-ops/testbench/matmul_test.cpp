/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <ctime>
#include <iostream>

#include "linear.hpp"
#include "matmul_top_accel.hpp"

using namespace std;

int main(int argc, char **argv) {
  float in_mat_a[ROWS][COLS];
  float in_mat_b[COLS][ROWS];
  float sw_result[ROWS][ROWS];
  ExactType hw_in_mat_a[ROWS][COLS];
  ExactType hw_in_mat_b[COLS][ROWS];
  ExactType hw_result[ROWS][ROWS];
  int err_cnt = 0;
  float inv_alpha = ROWS;
  float limit_factor = float(((1 << WL) - 1)) / float((1 << WL));

  srand(SEED);
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      in_mat_a[i][j] = limit_factor * (float)std::rand() / (float)RAND_MAX;
      in_mat_b[j][i] = limit_factor * (float)std::rand() / (float)RAND_MAX;
      in_mat_a[i][j] *= (j % 2 == 0 ? -1 : 1);
      in_mat_b[j][i] *= (j % 3 == 0 ? -1 : 1);
#if DATATYPE == 0
      hw_in_mat_a[i][j] = in_mat_a[i][j];
      hw_in_mat_b[j][i] = in_mat_b[j][i];
#else
      hw_in_mat_a[i][j] = in_mat_a[i][j] * (1 << WL);
      hw_in_mat_b[j][i] = in_mat_b[j][i] * (1 << WL);
#endif
    }
  }

  ama::sw::matmul<float, ROWS, COLS>(in_mat_a, in_mat_b, sw_result);
  matmul_top_accel(hw_in_mat_a, hw_in_mat_b, hw_result);

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
    }
  }
  ama::utils::compare_results<float, ROWS, ROWS>(hw_result_f, sw_result,
                                                 err_cnt, 0.05);
  ama::utils::sign_changes<float, ROWS, ROWS>(hw_result_f, sw_result);
  ama::utils::print_matrices<float, ROWS, ROWS>(hw_result_f);
  ama::utils::print_matrices<float, ROWS, COLS>(sw_result);
}
