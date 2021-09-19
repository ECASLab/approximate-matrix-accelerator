/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "matadd_top_accel.hpp"

#include "linear.hpp"

void matadd_top_accel(ExactType a[kCols * kRows], ExactType b[kCols * kRows],
                      ExactType res[kCols * kRows]) {
  ama::hw::matadd<ExactType, kRows, kCols>(a, b, res);
}
