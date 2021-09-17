/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once 

#include <iostream>

template <typename T, int M, int N>

/**
 * @brief Prints a matrix
 * @param flag A flag to determine which word between software
 * or hardware prints
 * @param hw_result A result matrix produced in
 * the hardware implementation to be printed
 * @param sw_result A result matrix produced in
 * the software implementation
 */
void print_matrices(const T hw_result[M][M], const T sw_result[M][M]) {
  for (int k = 0; k < 2; k++) {
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < M; j++) {
        if (k == 1) {
          std::cout << hw_result[i][j] << ' ';
        } else {
          std::cout << sw_result[i][j] << ' ';
        }
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}
