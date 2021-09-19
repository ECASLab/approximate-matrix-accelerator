/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <ctime>
#include <iostream>

#include "../../../../includes/linear.hpp"
#include "../tops/matadd_top_accel.hpp"

using namespace std;


int main(int argc, char **argv) {
  ExactType in_mat_a[kRows][kCols];
  ExactType in_mat_b[kRows][kCols];

  //srand(time(nullptr));
  for (int i = 0; i < kRows; i++) {
    for (int j = 0; j < kCols; j++) {
      in_mat_a[i][j] = 10 * (ExactType)rand() / (ExactType)RAND_MAX;
      in_mat_b[j][i] = 10 * (ExactType)rand() / (ExactType)RAND_MAX;
      in_mat_a[i][j] *= j % 2 ? -1 : 1;
      in_mat_b[j][i] *= j % 3 ? -1 : 1;
    }
  }
  
  int err_cnt = 0;
  ExactType hw_result[kRows][kCols], sw_result[kRows][kCols];
  ama::sw::matadd<ExactType,kRows,kCols>(in_mat_a, in_mat_b, sw_result);
  matadd_top_accel(in_mat_a, in_mat_b, hw_result);

  ama::utils::compare_results<ExactType,kRows,kCols>(hw_result, sw_result, err_cnt, 0.05);
  ama::utils::print_matrices<ExactType,kRows,kCols>(hw_result);
  ama::utils::print_matrices<ExactType,kRows,kCols>(sw_result);
}