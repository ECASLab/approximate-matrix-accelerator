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

  srand(SEED);
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      in_mat_a[i][j] = 0.5f * (float)std::rand() / (float)RAND_MAX;
      in_mat_b[j][i] = 0.5f * (float)std::rand() / (float)RAND_MAX;
      in_mat_a[i][j] *= (j % 2 ? -1 : 1);
      in_mat_b[j][i] *= (j % 3 ? -1 : 1);
      hw_in_mat_a[i][j] = in_mat_a[i][j];
      hw_in_mat_b[j][i] = in_mat_b[j][i];
    }
  }

  ama::sw::matmul<float, ROWS, COLS>(in_mat_a, in_mat_b, sw_result);
  matmul_top_accel(hw_in_mat_a, hw_in_mat_b, hw_result);

  ama::utils::compare_results<ExactType, float, ROWS, COLS>(
      hw_result, sw_result, err_cnt, 0.05);
  ama::utils::print_matrices<ExactType, ROWS, COLS>(hw_result);
  ama::utils::print_matrices<float, ROWS, COLS>(sw_result);
}
