/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <cmath>
#include <ctime>
#include <iostream>

#include "linear.hpp"
#include "matfma_top_accel.hpp"

using namespace std;

int main(int argc, char **argv) {
  ExactType in_mat_a[kRows][kCols];
  ExactType in_mat_b[kCols][kRows];
  ExactType in_mat_c[kCols][kCols];

  /*
  srand(time(nullptr));
  The previous code line is commented because when is used an error
  ocurrs in the cosimulation step. It generates that the software
  implementation matrix to be very different from the RTL implementation,
  that is, the hardware matrix
  */
  for (int i = 0; i < kRows; i++) {
    for (int j = 0; j < kCols; j++) {
      in_mat_a[i][j] = 10 * (ExactType)rand() / (ExactType)RAND_MAX;
      in_mat_b[j][i] = 10 * (ExactType)rand() / (ExactType)RAND_MAX;
      in_mat_a[i][j] *= j % 2 ? -1 : 1;
      in_mat_b[j][i] *= j % 3 ? -1 : 1;
    }
    for (int k = 0; k < kRows; k++) {
      in_mat_c[i][k] = 10 * (ExactType)rand() / (ExactType)RAND_MAX;
      in_mat_c[i][k] *= k % 5 ? -1 : 1;
    }
  }

  ExactType hw_result[kRows][kRows], sw_result[kRows][kRows];
  int err_cnt = 0;

  ama::sw::matfma<ExactType, kRows, kCols>(in_mat_a, in_mat_b, in_mat_c,
                                           sw_result);
  matfma_top_accel(in_mat_a, in_mat_b, in_mat_c, hw_result);

  ama::utils::compare_results<ExactType, kRows, kCols>(hw_result, sw_result,
                                                       err_cnt, 0.05);
  ama::utils::print_matrices<ExactType, kRows, kCols>(hw_result);
  ama::utils::print_matrices<ExactType, kRows, kCols>(sw_result);

  if (err_cnt)
    cout << "ERROR: " << err_cnt << " mismatches detected!" << endl;
  else
    cout << "Test passes." << endl;
  return err_cnt;
}
