/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <iostream>

#include "operations_top_accel.hpp"

using namespace std;

#define M 3
#define N 3

/**
 * @brief Matrix addition test
 * It compares the results of two matrices
 * @param in_mat_a Left Matrix to add
 * @param in_mat_b Right Matrix to add
 * @param res Matrix with the result
 */
void matadd_tb(const float in_mat_a[M][N], const float in_mat_b[N][N],
               float res[M][N]);

/**
 * @brief Matrix multiplication test
 * It compares the results of two matrices
 * @param in_mat_a Left Matrix to multiply
 * @param in_mat_b Right Matrix to multiply
 * @param res Matrix with the result
 */
void matmul_tb(const float in_mat_a[M][N], const float in_mat_b[N][N],
               float res[M][N]);

/**
 * @brief Results test comparison
 * It compares the results of two matrices
 * @param hw_result Left Matrix to compare
 * It represents the result of hardware
 * implementation
 * @param sw_result Right Matrix to compare
 * It represents the result of software
 * implementation
 * @param sub_err_cnt accumulate the amount of errors
 */
void compare_results(float hw_result[M][N], float sw_result[M][N],
                     int &sub_err_cnt);

/**
 * @brief Prints a matrix
 * @param res A result matrix produced in
 * the testbench to be printed
 * @param err_cnt accumulate the amount of errors
 */
void print_matrices(const float res[M][N]);

int main(int argc, char **argv) {
  const float in_mat_a[M][N] = {
      {2.3, 4.5, 1.8}, {3.3, 0.7, 0.0}, {5.0, 6.8, 9.9}};
  const float in_mat_b[N][N] = {
      {1.4, 8.2, 14.1}, {0.2, 1.4, 1.0}, {11.11, 6.3, 7.2}};
  const float in_mat_c[M][N] = {
      {1.9, 6.7, 2.2}, {7.7, 8.8, 1.1}, {3.3, 4.4, 5.5}};
  float hw_result[M][N], sw_result[M][N];
  int sub_err_cnt = 0;
  int err_cnt = 0;

  for (int selection = 0; selection < 3; selection++) {
    switch (selection) {
      case 0:
        matadd_tb(in_mat_a, in_mat_b, sw_result);
        operations_top_accel(selection, in_mat_a, in_mat_b, in_mat_c,
                             hw_result);
        compare_results(hw_result, sw_result, sub_err_cnt);
        if (sub_err_cnt) {
          cout << "ERROR: " << sub_err_cnt
               << " mismatches in matrices sum detected!" << endl;
          err_cnt += sub_err_cnt;
          sub_err_cnt = 0;
        }
        cout << "Printing hardware result matrix for the addiction" << endl;
        print_matrices(hw_result);
        cout << "Printing software result matrix for the addiction" << endl;
        print_matrices(sw_result);
        break;
      case 1:
        matmul_tb(in_mat_a, in_mat_b, sw_result);
        operations_top_accel(selection, in_mat_a, in_mat_b, in_mat_c,
                             hw_result);
        compare_results(hw_result, sw_result, sub_err_cnt);
        if (sub_err_cnt) {
          cout << "ERROR: " << sub_err_cnt
               << " mismatches in matrices multiplication detected!" << endl;
          err_cnt += sub_err_cnt;
          sub_err_cnt = 0;
        }
        cout << "Printing hardware result matrix for the multiplication"
             << endl;
        print_matrices(hw_result);
        cout << "Printing software result matrix for the multiplication"
             << endl;
        print_matrices(sw_result);
        break;
      case 2:
        matmul_tb(in_mat_a, in_mat_b, sw_result);
        matadd_tb(in_mat_c, sw_result, sw_result);
        operations_top_accel(selection, in_mat_a, in_mat_b, in_mat_c,
                             hw_result);
        compare_results(hw_result, sw_result, sub_err_cnt);
        if (sub_err_cnt) {
          cout << "ERROR: " << sub_err_cnt
               << " mismatches in matrices accumulator detected!" << endl;
          err_cnt += sub_err_cnt;
          sub_err_cnt = 0;
        }
        cout << "Printing hardware result matrix for the accumulator" << endl;
        print_matrices(hw_result);
        cout << "Printing software result matrix for the accumulator" << endl;
        print_matrices(sw_result);
        break;
    }
  }

  if (err_cnt)
    cout << "ERROR: " << err_cnt << " mismatches detected!" << endl;
  else
    cout << "Test passes." << endl;
  return err_cnt;
}

void matadd_tb(const float in_mat_a[M][N], const float in_mat_b[N][N],
               float res[M][N]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      res[i][j] = in_mat_a[i][j] + in_mat_b[i][j];
    }
  }
}

void matmul_tb(const float in_mat_a[M][N], const float in_mat_b[N][N],
               float res[M][N]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      res[i][j] = 0;
      for (int k = 0; k < N; k++) {
        res[i][j] += in_mat_a[i][k] * in_mat_b[k][j];
      }
    }
  }
}

void compare_results(float hw_result[M][N], float sw_result[M][N],
                     int &err_cnt) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (hw_result[i][j] != sw_result[i][j]) {
        cout << "It occurs a mismatches in indices " << '[' << i << ']' << '['
             << j << ']' << endl;
        err_cnt++;
      }
    }
  }
}

void print_matrices(const float res[M][N]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      cout << res[i][j] << ' ';
    }
    cout << endl;
  }
  cout << endl;
}
