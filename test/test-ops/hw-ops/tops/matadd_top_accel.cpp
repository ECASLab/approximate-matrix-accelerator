/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "../../../../includes/linear.hpp"
#include "matadd_top_accel.hpp"

void matadd_top_accel(const ExactType a[kRows][kCols],
                      const ExactType b[kCols][kRows],
                      ExactType res[kRows][kCols]) {
  ama::hw::matadd<ExactType, kRows, kCols>(a, b, res);
}
