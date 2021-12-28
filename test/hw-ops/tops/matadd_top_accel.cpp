/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "matadd_top_accel.hpp"

#include "linear.hpp"

/* Toggle the USE_V0 switch to use the former version */
// #define USE_V0

void matadd_top_accel(ExactType a[ROWS][COLS], ExactType b[ROWS][COLS],
                      ExactType res[ROWS][COLS]) {
#ifdef USE_V0
  ama::hw::core::matadd<ExactType, ROWS, COLS>(a, b, res);
#else
  auto engine = ama::hw::operators::MatrixAdd<ExactType, ROWS, COLS>{};
  engine.Execute(a, b, res);
#endif
}
