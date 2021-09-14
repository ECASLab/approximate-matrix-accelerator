/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <iostream>
#include <ctime>

#include "operations_top_accel.hpp"

using namespace std;

using ExactType = float;

#define M 16
#define N 16

/**
 * @brief Matrix addition test
 * It compares the results of two matrices
 * @param in_mat_a Left Matrix to add
 * @param in_mat_b Right Matrix to add
 * @param res Matrix with the result
 */
void matadd_tb(const ExactType in_mat_a[M][M], const ExactType in_mat_b[M][M],
               ExactType res[M][M]);

/**
 * @brief Matrix multiplication test
 * It compares the results of two matrices
 * @param in_mat_a Left Matrix to multiply
 * @param in_mat_b Right Matrix to multiply
 * @param res Matrix with the result
 */
void matmul_tb(const ExactType in_mat_a[M][N], const ExactType in_mat_b[N][M],
               ExactType res[M][M]);

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
void compare_results(int selection, ExactType hw_result[M][M],
                     ExactType sw_result[M][M], int &err_cnt);

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
void print_matrices(int selection, const int flag[2], ExactType hw_result[M][M],
                    ExactType sw_result[M][M]);

int main(int argc, char **argv) {
  ExactType in_mat_a[M][N];
  ExactType in_mat_b[N][M];
  ExactType in_mat_c[M][M];

  srand(time(nullptr));
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

void matadd_tb(const ExactType in_mat_a[M][M], const ExactType in_mat_b[M][M],
               ExactType res[M][M]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
      res[i][j] = in_mat_a[i][j] + in_mat_b[i][j];
    }
  }
}

void matmul_tb(const ExactType in_mat_a[M][N], const ExactType in_mat_b[N][M],
               ExactType res[M][M]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
      res[i][j] = 0;
      for (int k = 0; k < N; k++) {
        res[i][j] += in_mat_a[i][k] * in_mat_b[k][j];
      }
    }
  }
}

void compare_results(int selection, ExactType hw_result[M][M],
                     ExactType sw_result[M][M], int &err_cnt) {
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

void print_matrices(int selection, const int flag[2], ExactType hw_result[M][M],
                    ExactType sw_result[M][M]) {
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
