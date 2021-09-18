/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <ctime>
#include <cmath>
#include <iostream>

#include "../../includes/operations.hpp"
#include "operations_top_accel.hpp"

using namespace std;

#define M 12
#define N 12

int main(int argc, char **argv) {
  ExactType in_mat_a[M][N];
  ExactType in_mat_b[N][M];
  ExactType in_mat_c[M][M];

  //srand(time(nullptr));
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      in_mat_a[i][j] = 10 * (ExactType)rand() / (ExactType)RAND_MAX;
      in_mat_b[j][i] = 10 * (ExactType)rand() / (ExactType)RAND_MAX;
    }
    for (int k = 0; k < M; k++) {
      in_mat_c[i][k] = 10 * (ExactType)rand() / (ExactType)RAND_MAX;
    }
  }

  ExactType hw_result[M][M], sw_result[M][M];
  const int flag[2] = {0, 1};
  int err_cnt = 0;
  string word[3] = {"sum", "multiplication", "accumulator"};
  string words[2] = {"hardware", "software"};

  for (int selection = 0; selection < 3; selection++) {
    switch (selection) {
      case 0:
        ama::sw::matadd<ExactType,kRows,kRows>(in_mat_c, in_mat_c, sw_result);
        operations_top_accel(selection, in_mat_a, in_mat_b, in_mat_c,
                             hw_result);
        break;
      case 1:
        ama::sw::matmul<ExactType,kRows,kCols>(in_mat_a, in_mat_b, sw_result);
        operations_top_accel(selection, in_mat_a, in_mat_b, in_mat_c,
                             hw_result);
        break;
      case 2:
        ama::sw::matmac<ExactType,kRows,kCols>(in_mat_a, in_mat_b, in_mat_c, sw_result);
        operations_top_accel(selection, in_mat_a, in_mat_b, in_mat_c,
                             hw_result);
        break;
    }
    ama::utils::compare_results<ExactType,kRows,kCols>(hw_result, sw_result, err_cnt, 0.05);
    
    for(int k = 0; k < 2; k++){
      cout << "Printing " << words[flag[k]] << " result matrix for the "
         << word[selection] << endl;
      if( k == 1){
        ama::utils::print_matrices<ExactType,kRows,kRows>(hw_result);
      }
      else{
        ama::utils::print_matrices<ExactType,kRows,kRows>(sw_result);
      }
    }
  }

  if (err_cnt)
    cout << "ERROR: " << err_cnt << " mismatches detected!" << endl;
  else
    cout << "Test passes." << endl;
  return err_cnt;
}
