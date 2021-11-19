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
      #if DATATYPE == 0
        hw_in_mat_a[i][j] = in_mat_a[i][j];
        hw_in_mat_b[j][i] = in_mat_b[j][i];
      #else 
        hw_in_mat_a[i][j] = in_mat_a[i][j] * (1 << (WL-1));
        hw_in_mat_b[j][i] = in_mat_b[j][i] * (1 << (WL-1));
      #endif
      //hw_in_mat_a[i][j] = DATATYPE == 0 ? in_mat_a[i][j] : in_mat_a[i][j] * (1 << (WL - 1));
      //std::cout << "software " << in_mat_a[i][j] << std::endl;
      //std::cout << "hardware " << hw_in_mat_a[i][j] << std::endl;
      //hw_in_mat_b[j][i] = in_mat_b[j][i];
    }
  }
  
  ama::sw::matmul<float, ROWS, COLS>(in_mat_a, in_mat_b, sw_result);
  matmul_top_accel(hw_in_mat_a, hw_in_mat_b, hw_result);

#if DATATYPE == 0
  ama::utils::compare_results<ExactType, float, ROWS, COLS>(hw_result, sw_result, err_cnt, 0.05);
  ama::utils::sign_changes<ExactType, float, ROWS, COLS>(hw_result, sw_result);
  ama::utils::print_matrices<ExactType, ROWS, COLS>(hw_result);
#else
  float hw_result_f[ROWS][ROWS];
  float scale = float(1) / (float)(1 << (WL-1));
  //ama::utils::print_matrices<ExactType, ROWS, COLS>(hw_result);
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < ROWS; ++j) {
      //std::cout << scale << std::endl;
      //std::cout<<hw_result[i][j]<<endl;
      hw_result_f[i][j] = static_cast<float>(hw_result[i][j]) * scale;
    }
  }
  ama::utils::compare_results<float, float, ROWS, COLS>(hw_result_f, sw_result, err_cnt, 0.05);
  ama::utils::print_matrices<float, ROWS, COLS>(hw_result_f);
#endif

  //ama::utils::compare_results<ExactType, float, ROWS, COLS>(
      //DATATYPE == 0 ? hw_result : hw_result_f, sw_result, err_cnt, 0.05);
  //ama::utils::print_matrices<ExactType, ROWS, COLS>(hw_result);
  ama::utils::print_matrices<float, ROWS, COLS>(sw_result);
}
