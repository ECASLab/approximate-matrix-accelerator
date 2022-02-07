/*
 * Copyright 2022
 * Author: Fabricio Elizondo Fernandez <faelizondo@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <iomanip>
#include <iostream>

namespace ama {
namespace utils {

template <typename T, int K>
void print_vectors(T result[K]) {
  std::cout << std::setprecision(6) << std::fixed;
  for (int i = 0; i < K; i++) {
    std::cout << static_cast<float>(result[i]) << ' ';
  }
  std::cout << std::endl;
}
}  // namespace utils
}  // namespace ama
