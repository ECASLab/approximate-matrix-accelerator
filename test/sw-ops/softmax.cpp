/*
 * Copyright 2022
 * Author: Fabricio Elizondo Fernandez <faelizondo@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <stdlib.h>
#include <ctime>
#include <iostream>

#include "linear.hpp"
#include "testbench.hpp"

int main() {
  ExactType z[kCols];
  ExactType res[kCols];

  for (int i = 0; i < kCols; i++) {
    z[i] = 10 * (ExactType)rand() / (ExactType)RAND_MAX;
  }

  ama::sw::softmax<ExactType, kCols>(z, res);
  ama::utils::print_vectors<ExactType, kCols>(z);
  ama::utils::print_vectors<ExactType, kCols>(res);
  ExactType x{2};
  ExactType exp_approx = ama::sw::interpolation::linear<ExactType>(x);
  ExactType exp_approx2 = ama::sw::interpolation::quadratic<ExactType>(x);
  std::cout << std::setprecision(30) << std::fixed;
  std::cout << std::exp(2) << std::endl;
  std::cout << exp_approx << std::endl;
  std::cout << exp_approx2 << std::endl;
}
