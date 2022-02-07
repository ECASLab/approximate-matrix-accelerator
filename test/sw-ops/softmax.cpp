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
  ama::sw::taylor_sotfmax<ExactType, kCols>(z, res);
  ama::utils::print_vectors<ExactType, kCols>(z);
  ama::utils::print_vectors<ExactType, kCols>(res);
  ama::sw::pade_softmax<ExactType, kCols>(z, res);
  ama::utils::print_vectors<ExactType, kCols>(z);
  ama::utils::print_vectors<ExactType, kCols>(res);
}
