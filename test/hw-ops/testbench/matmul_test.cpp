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
  float in_mat_a[kRows][kCols];
  float in_mat_b[kCols][kRows];
  float sw_result[kRows][kRows];
  ExactType hw_in_mat_a[kRows][kCols];
  ExactType hw_in_mat_b[kCols][kRows];
  ExactType hw_result[kRows][kRows];
  int err_cnt = 0;

  srand(kSeed);
  for (int i = 0; i < kRows; i++) {
    for (int j = 0; j < kCols; j++) {
      in_mat_a[i][j] = 0.5f * (float)std::rand() / (float)RAND_MAX;
      in_mat_b[j][i] = 0.5f * (float)std::rand() / (float)RAND_MAX;
      in_mat_a[i][j] *= (j % 2 ? -1 : 1);
      in_mat_b[j][i] *= (j % 3 ? -1 : 1);
      hw_in_mat_a[i][j] = in_mat_a[i][j];
      hw_in_mat_b[j][i] = in_mat_b[j][i];
    }
  }

  ama::sw::matmul<float, kRows, kCols>(in_mat_a, in_mat_b, sw_result);
  matmul_top_accel(hw_in_mat_a, hw_in_mat_b, hw_result);

  ama::utils::compare_results<ExactType, float, kRows, kCols>(
      hw_result, sw_result, err_cnt, 0.05);
  ama::utils::print_matrices<ExactType, kRows, kCols>(hw_result);
  ama::utils::print_matrices<float, kRows, kCols>(sw_result);
}
