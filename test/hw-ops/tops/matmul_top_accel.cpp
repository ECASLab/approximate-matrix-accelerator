/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "linear.hpp"
#include "matmac_top_accel.hpp"

void matmul_top_accel(const ExactType a[kRows][kCols],
                      const ExactType b[kCols][kRows],
                      ExactType res[kRows][kRows]) {
//#pragma HLS ARRAY_PARTITION variable=a complete dim=0
//#pragma HLS ARRAY_PARTITION variable=b complete dim=0
//#pragma HLS ARRAY_PARTITION variable=res complete dim=0
#pragma HLS ARRAY_RESHAPE variable=res complete dim=2
#pragma HLS ARRAY_RESHAPE variable=b complete dim=1
#pragma HLS ARRAY_RESHAPE variable=a complete dim=2
  ama::hw::matmul<ExactType, kRows, kCols>(a, b, res);
}
