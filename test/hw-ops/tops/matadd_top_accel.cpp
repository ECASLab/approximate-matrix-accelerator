/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "linear.hpp"
#include "matadd_top_accel.hpp"

void matadd_top_accel(ExactType a[kRows][kCols], ExactType b[kRows][kCols],
                      ExactType res[kRows][kCols]) {
#pragma HLS ARRAY_RESHAPE variable=res complete dim=2
#pragma HLS ARRAY_RESHAPE variable=b complete dim=2
#pragma HLS ARRAY_RESHAPE variable=a complete dim=2
  ama::hw::matadd<ExactType, kRows, kCols>(a, b, res);
}
