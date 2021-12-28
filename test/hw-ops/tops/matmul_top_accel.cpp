/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "matmul_top_accel.hpp"

#include "linear.hpp"

/* Toggle the USE_V0 switch to use the former version */
// #define USE_V0

void matmul_top_accel(const ExactType a[ROWS][COLS],
                      const ExactType b[COLS][ROWS],
                      ExactType res[ROWS][ROWS]) {
#ifdef USE_V0
  ama::hw::core::matmul<ExactType, ROWS, COLS>(a, b, res);
#else
  auto engine = ama::hw::operators::MatrixMultiply<ExactType, ROWS, COLS>{};
  engine.Execute(a, b, res);
#endif
}
