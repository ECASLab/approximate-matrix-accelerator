/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once
 
namespace ama{
namespace core{

/**
 * @brief Multiply
 * It performs a multiplication of two numbers.
 * @tparam T Data type
 * @param a Left parameter to multiply
 * @param b Right parameter to multiply
 */
template <typename T>
T mul(const T a, const T b) {
#pragma HLS INLINE off
  return a * b;
}
}
}
