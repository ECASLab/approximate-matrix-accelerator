/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "matmul_top_accel.hpp"

#include "linear.hpp"

void matmul_top_accel(const ExactType a[ROWS][COLS],
                      const ExactType b[COLS][ROWS],
                      ExactType res[ROWS][ROWS]) {
  ama::hw::core::matmul<ExactType, ROWS, COLS>(a, b, res);
}
