/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <ctime>
#include <iostream>
#include <cmath> 

#include "fma_top_accel.hpp"

using namespace std;

#define M 16
#define N 16
#define TOLERANCE 0.05

/**
 * @brief Fused Multiply-Add test
 * It performs the multiplication and the addition in one step.
 * @param a Left Matrix to multiply
 * @param b Right Matrix to multiply
 * @param c Right Matrix to add
 * @param res Matrix with the result
 */
void fma_tb(const ExactType a[M][N], const ExactType b[N][M],
            const ExactType c[M][M], ExactType res[M][M]);
/**
 * @brief Results test comparison
 * @param hw_result Left Matrix to compare
 * It represents the result of hardware
 * implementation
 * @param sw_result Right Matrix to compare
 * It represents the result of software
 * implementation
 * @param err_cnt accumulate the total amount of errors
 */
void compare_results(ExactType hw_result[M][M], ExactType sw_result[M][M],
                     int &err_cnt);

/**
 * @brief Prints a matrix
 * @param flag A flag to determine which word between software
 * or hardware prints
 * @param hw_result A result matrix produced in
 * the hardware implementation to be printed
 * @param sw_result A result matrix produced in
 * the software implementation
 */
void print_matrices(ExactType hw_result[M][M], ExactType sw_result[M][M]);

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
  int err_cnt = 0;

  fma_tb(in_mat_a, in_mat_b, in_mat_c, sw_result);
  fma_top_accel(in_mat_a, in_mat_b, in_mat_c, hw_result);

  compare_results(hw_result, sw_result, err_cnt);
  print_matrices(hw_result, sw_result);

  if (err_cnt)
    cout << "ERROR: " << err_cnt << " mismatches detected!" << endl;
  else
    cout << "Test passes." << endl;
  return err_cnt;
}

void fma_tb(const ExactType a[M][N], const ExactType b[N][M],
            const ExactType c[M][M], ExactType res[M][M]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
      res[i][j] = c[i][j];
      for (int k = 0; k < N; k++) {
        res[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

void compare_results(ExactType hw_result[M][M], ExactType sw_result[M][M],
                     int &err_cnt) {
  ExactType relative_error = 0;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
      relative_error = abs(hw_result[i][j] - sw_result[i][j]) / sw_result[i][j];
      if (relative_error > TOLERANCE) {
    	cout << relative_error << endl;
        cout << "It occurs a mismatches in indices " << '[' << i << ']' << '['
             << j << ']' << endl;
        err_cnt++;
      }
    }
  }
}

void print_matrices(ExactType hw_result[M][M], ExactType sw_result[M][M]) {
  for (int k = 0; k < 2; k++) {
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
