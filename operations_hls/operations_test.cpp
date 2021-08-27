#include <iostream>

#include "operations_top.hpp"

using namespace std;

#define MAT_A_ROWS 3
#define MAT_A_COLS 3
#define MAT_B_ROWS 3
#define MAT_B_COLS 3

void compare_results(float hw_result[MAT_A_ROWS][MAT_B_COLS],
                     float sw_result[MAT_A_ROWS][MAT_B_COLS], int err_cnt);

void matadd_tb(const float in_mat_a[MAT_A_ROWS][MAT_A_COLS],
               const float in_mat_b[MAT_B_ROWS][3],
               float res[MAT_A_ROWS][MAT_B_COLS]);

void matmul_tb(const float in_mat_a[MAT_A_ROWS][MAT_A_COLS],
               const float in_mat_b[MAT_B_ROWS][3],
               float res[MAT_A_ROWS][MAT_B_COLS]);

int main(int argc, char **argv) {
  const float in_mat_a[MAT_A_ROWS][MAT_A_COLS] = {
      {2.3, 4.5, 1.8}, {3.3, 0.7, 0.0}, {5.0, 6.8, 9.9}};
  const float in_mat_b[MAT_B_ROWS][MAT_B_COLS] = {
      {1.4, 8.2, 14.1}, {0.2, 1.4, 1.0}, {11.11, 6.3, 7.2}};
  const float in_mat_c[MAT_A_ROWS][MAT_B_COLS] = {
      {1.9, 6.7, 2.2}, {7.7, 8.8, 1.1}, {3.3, 4.4, 5.5}};
  float hw_result[MAT_A_ROWS][MAT_B_COLS], sw_result[MAT_A_ROWS][MAT_B_COLS];
  int err_cnt = 0;

  for (int selection = 0; selection < 3; selection++) {
    switch (selection) {
      case 0:
        matadd_tb(in_mat_a, in_mat_b, sw_result);
        operations_top(selection, in_mat_a, in_mat_b, in_mat_c, hw_result);
        compare_results(hw_result, sw_result, err_cnt);
        if (err_cnt)
          cout << "ERROR: " << err_cnt
               << " mismatches in matrices sum detected!" << endl;
        break;
      case 1:
        matmul_tb(in_mat_a, in_mat_b, sw_result);
        operations_top(selection, in_mat_a, in_mat_b, in_mat_c, hw_result);
        compare_results(hw_result, sw_result, err_cnt);
        if (err_cnt)
          cout << "ERROR: " << err_cnt
               << " mismatches in matrices multiplication detected!" << endl;
        break;
      case 2:
        matmul_tb(in_mat_a, in_mat_b, sw_result);
        matadd_tb(in_mat_c, sw_result, sw_result);
        operations_top(selection, in_mat_a, in_mat_b, in_mat_c, hw_result);
        compare_results(hw_result, sw_result, err_cnt);
        if (err_cnt)
          cout << "ERROR: " << err_cnt
               << " mismatches in matrices multiplication and adding detected!"
               << endl;
        break;
    }
  }

  if (err_cnt)
    cout << "ERROR: " << err_cnt << " mismatches detected!" << endl;
  else
    cout << "Test passes." << endl;
  return err_cnt;
}

void matadd_tb(const float in_mat_a[MAT_A_ROWS][MAT_A_COLS],
               const float in_mat_b[MAT_B_ROWS][3],
               float res[MAT_A_ROWS][MAT_B_COLS]) {
  for (int i = 0; i < MAT_A_ROWS; i++) {
    for (int j = 0; j < MAT_B_COLS; j++) {
      res[i][j] = in_mat_a[i][j] + in_mat_b[i][j];
    }
  }
}

void compare_results(float hw_result[MAT_A_ROWS][MAT_B_COLS],
                     float sw_result[MAT_A_ROWS][MAT_B_COLS], int err_cnt) {
  for (int i = 0; i < MAT_A_ROWS; i++) {
    for (int j = 0; j < MAT_B_COLS; j++) {
      if (hw_result[i][j] != sw_result[i][j]) err_cnt++;
      cout << sw_result[i][j] << endl;
    }
  }
}

void matmul_tb(const float in_mat_a[MAT_A_ROWS][MAT_A_COLS],
               const float in_mat_b[MAT_B_ROWS][3],
               float res[MAT_A_ROWS][MAT_B_COLS]) {
  for (int i = 0; i < MAT_A_ROWS; i++) {
    for (int j = 0; j < MAT_B_COLS; j++) {
      res[i][j] = 0;
      for (int k = 0; k < MAT_B_ROWS; k++) {
        res[i][j] += in_mat_a[i][k] * in_mat_b[k][j];
      }
    }
  }
}
