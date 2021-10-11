/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "linear.hpp"
#include "matadd_top_accel.hpp"

void matadd_top_accel(ExactType a[kRows][kCols], ExactType b[kRows][kCols],
                      ExactType res[kRows][kCols]) {
  ama::hw::matadd<ExactType, kRows, kCols>(a, b, res);
}
