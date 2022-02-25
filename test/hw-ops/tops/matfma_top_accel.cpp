/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

/**
 * @example matfma_top_accel.cpp
 * Matrix addition example
 */

#include "matfma_top_accel.hpp"

#include "linear.hpp"

/* Toggle the USE_V0 switch to use the former version */
// #define USE_V0

void matfma_top_accel(const ExactType a[ROWS][COLS],
                      const ExactType b[COLS][ROWS],
                      const ExactType c[ROWS][ROWS],
                      ExactType res[ROWS][ROWS]) {
#ifdef USE_V0
  ama::hw::core::matfma<ExactType, ROWS, COLS>(a, b, c, res);
#else
  auto engine = ama::hw::operators::MatrixMultiplyAdd<ExactType, ROWS, COLS>{};
  engine.Execute(a, b, c, res);
#endif
}
