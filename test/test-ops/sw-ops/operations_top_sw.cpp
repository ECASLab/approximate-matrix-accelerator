/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <iostream>

#include "../../../includes/sw-ops/matmac.hpp"
#include "../../../includes/sw-ops/matadd.hpp"
#include "../../../includes/sw-ops/matmul.hpp"
#include "../../../includes/sw-ops/operations_top_sw.hpp"

void operations_top_sw(int selection, const float a[kRows][kCols],
                       const float b[kCols][kRows], const float c[kRows][kRows],
                       float res[kRows][kRows]) {
  switch (selection) {
    case 0:
      ama::sw::matadd<float, kRows>(c, c, res);
      break;
    case 1:
      ama::sw::matmul<float, kRows, kCols>(a, b, res);
      break;
    case 2:
      ama::sw::matmac<float, kRows, kCols>(a, b, c, res);
      break;
  }
} 

/**
 * @brief Prints a matrix
 * @param res print the result matrix
 */
void print_matrix(const float res[kRows][kRows]){
  for(int i = 0; i < kRows; i++){
    for(int j = 0; j < kRows; j++){
      std::cout << res[i][j] << ' ';
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int main() {
  const float a[4][3] = {{2.3, 4.5, 1.8}, 
                        {3.3, 0.7, 0.0}, 
                        {5.0, 6.8, 9.9},
                        {28.1, 2.96, 12.4}};

  const float b[3][4] = {{1.4, 8.2, 14.1, 61.2}, 
                        {0.2, 1.4, 1.0, 2.2}, 
                        {11.11, 6.3, 7.2, 74.2}};

  const float c[4][4] = {{1.9, 6.7, 2.2, 1.6}, 
                        {7.7, 8.8, 1.1, 2.0}, 
                        {3.3, 4.4, 5.5, 9.9},
                        {4.2, 6.4, 8.6, 10.8}};

  float res[4][4];
  operations_top_sw(2, a, b, c, res);
  print_matrix(res);
  return 0;
}
