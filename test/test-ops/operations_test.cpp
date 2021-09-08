/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <iostream>

#include "operations_top_accel.hpp"

using namespace std;

#define M 4 
#define N 5

/**
 * @brief Matrix addition test
 * It compares the results of two matrices
 * @param in_mat_a Left Matrix to add
 * @param in_mat_b Right Matrix to add
 * @param res Matrix with the result
 */
void matadd_tb(const float in_mat_a[M][M], const float in_mat_b[M][M],
               float res[M][M]);

/**
 * @brief Matrix multiplication test
 * It compares the results of two matrices
 * @param in_mat_a Left Matrix to multiply
 * @param in_mat_b Right Matrix to multiply
 * @param res Matrix with the result
 */
void matmul_tb(const float in_mat_a[M][N], const float in_mat_b[N][M],
               float res[M][M]);

/**
 * @brief Results test comparison
 * It compares the results of two matrices
 * @param selection A flag to determine which word between sum,
 * multiplication or accumulate prints
 * @param hw_result Left Matrix to compare
 * It represents the result of hardware
 * implementation
 * @param sw_result Right Matrix to compare
 * It represents the result of software
 * implementation
 * @param err_cnt accumulate the total amount of errors
 */
void compare_results(int selection, float hw_result[M][M],
                     float sw_result[M][M], int &err_cnt);

/**
 * @brief Prints a matrix
 * @param selection A flag to determine which word between sum,
 * multiplication or accumulate prints
 * @param flag A flag to determine which word between software
 * or hardware prints
 * @param hw_result A result matrix produced in
 * the hardware implementation to be printed
 * @param sw_result A result matrix produced in
 * the software implementation
 */
void print_matrices(int selection, const int flag[2], float hw_result[M][M],
                    float sw_result[M][M]);

int main(int argc, char **argv) {
  const float in_mat_a[M][N] = {
      {2.3, 4.5, 1.8, 14.6, 19.9}, 
      {3.3, 0.7, 0.0, 22.2, 17.7}, 
      {5.0, 6.8, 9.9, 16.7, 13.3},
      {10.2, 11.1, 12.5, 15.2, 22.2}};
  const float in_mat_b[N][M] = {
      {1.4, 8.2, 14.1, 22.2 }, 
      {0.2, 1.4, 1.0, 15.2 }, 
      {11.11, 6.3, 7.2, 14.6},
      {5.0, 6.8, 2.3, 4.5},
      {17.7, 22.2, 19.9, 5.0}};
  const float in_mat_c[M][M] = {
      {1.9, 6.7, 2.2, 8.2}, 
      {7.7, 8.8, 1.1, 6.3}, 
      {3.3, 4.4, 5.5, 6.8},
      {1.8, 14.6, 11.1, 12.5}};
  float hw_result[M][M], sw_result[M][M];
  const int flag[2] = {0, 1};
  int err_cnt = 0;

  for (int selection = 0; selection < 3; selection++) {
    switch (selection) {
      case 0:
        matadd_tb(in_mat_c, in_mat_c, sw_result);
        operations_top_accel(selection, in_mat_a, in_mat_b, in_mat_c,
                             hw_result);
        break;
      case 1:
        matmul_tb(in_mat_a, in_mat_b, sw_result);
        operations_top_accel(selection, in_mat_a, in_mat_b, in_mat_c,
                             hw_result);
        break;
      case 2:
        matmul_tb(in_mat_a, in_mat_b, sw_result);
        matadd_tb(in_mat_c, sw_result, sw_result);
        operations_top_accel(selection, in_mat_a, in_mat_b, in_mat_c,
                             hw_result);
        break;
    }
    compare_results(selection, hw_result, sw_result, err_cnt);
    print_matrices(selection, flag, hw_result, sw_result);
  }

  if (err_cnt)
    cout << "ERROR: " << err_cnt << " mismatches detected!" << endl;
  else
    cout << "Test passes." << endl;
  return err_cnt;
}

void matadd_tb(const float in_mat_a[M][M], const float in_mat_b[M][M],
               float res[M][M]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
      res[i][j] = in_mat_a[i][j] + in_mat_b[i][j];
    }
  }
}

void matmul_tb(const float in_mat_a[M][N], const float in_mat_b[N][M],
               float res[M][M]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
      res[i][j] = 0;
      for (int k = 0; k < N; k++) {
        res[i][j] += in_mat_a[i][k] * in_mat_b[k][j];
      }
    }
  }
}

void compare_results(int selection, float hw_result[M][M],
                     float sw_result[M][M], int &err_cnt) {
  int sub_err_cnt = 0;
  string word[3] = {"sum", "multiplication", "accumulator"};
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
      if (hw_result[i][j] != sw_result[i][j]) {
        cout << "It occurs a mismatches in indices " << '[' << i << ']' << '['
             << j << ']' << endl;
        sub_err_cnt++;
      }
    }
  }
  if (sub_err_cnt) {
    cout << "ERROR: " << sub_err_cnt << " mismatches in matrices "
         << word[selection] << " detected!" << endl;
    err_cnt += sub_err_cnt;
  }
}

void print_matrices(int selection, const int flag[2], float hw_result[M][M],
                    float sw_result[M][M]) {
  string word[3] = {"sum", "multiplication", "accumulator"};
  string words[2] = {"hardware", "software"};

  for (int k = 0; k < 2; k++) {
    cout << "Printing " << words[flag[k]] << " result matrix for the "
         << word[selection] << endl;
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < M; j++) {
        if (k == 1) {
          cout << hw_result[i][j] << ' ';
        } else {
          cout << sw_result[i][j] << ' ';
        }
      }
      cout << endl;
    }
    cout << endl;
  }
}
