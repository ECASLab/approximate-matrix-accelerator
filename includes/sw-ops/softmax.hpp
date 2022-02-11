/*
 * Copyright 2022
 * Author: Fabricio Elizondo Fernandez <faelizondo@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <cmath>

namespace ama {
namespace sw {

/**
 * @brief Softmax
 * It performs the softmax activation function
 * @tparam T Data type
 * @tparam K size of vector z
 * @param z Input data vector
 * @param res Vector with the result
 */



/* Exact version of Softmax */
template <typename T, int K>
void softmax(const T z[K], T res[K]) {
  T exp_sum;
  T max_arg = z[0];

  for (int i = 1; i < K; ++i) {
    if (max_arg < z[i]) {
      max_arg = z[i];
    }
  }

  for (int i = 0; i < K; ++i) {
    res[i] = std::exp(z[i] - max_arg);
    exp_sum += res[i];
  }

  for (int i = 0; i < K; ++i) {
    res[i] /= exp_sum;
  }
}

/* Taylor approximation Softmax, order 3 */
template<typename T, int K>
void taylor_sotfmax(const T z[K], T res[K]) {
  const float taylor_factor = 1.0f/6.0f;
  T exp_sum;

  for (int i = 0; i < K; ++i){
    res[i] = 1 + z[i] + 0.5 * std::pow(z[i], 2) + taylor_factor * std::pow(z[i], 3);
    exp_sum += res[i]; 
  }

  for (int i = 0; i < K; ++i) {
    res[i] /= exp_sum;
  }
}

/* Pade approximation Softmax, order 3/3 */
template<typename T, int K>
void pade_softmax(const T z[K], T res[K]) {
  T exp_sum;

  for (int i = 0; i < K; ++i) {
    res[i] = 120 + 60 * z[i] + 12 * std::pow(z[i], 2) + std::pow(z[i], 3) /
             120 - 60 * z[i] + 12 * std::pow(z[i], 2) - std::pow(z[i], 3);
    exp_sum += res[i];
  }

  for (int i = 0; i < K; ++i) {
    res[i] /= exp_sum;
  }
}

}  // namespace sw
}  // namespace ama
