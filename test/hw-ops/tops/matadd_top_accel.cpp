/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "linear.hpp"
#include "matadd_top_accel.hpp"

void matadd_top_accel(ExactType a[ROWS][COLS], ExactType b[ROWS][COLS],
                      ExactType res[ROWS][COLS]) {
  ama::hw::matadd<ExactType, ROWS, COLS>(a, b, res);
}
