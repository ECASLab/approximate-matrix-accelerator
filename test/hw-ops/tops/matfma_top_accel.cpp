/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "linear.hpp"
#include "matfma_top_accel.hpp"

void matfma_top_accel(const ExactType a[kRows][kCols],
                      const ExactType b[kCols][kRows],
                      const ExactType c[kRows][kRows],
                      ExactType res[kRows][kRows]) {
#pragma HLS INTERFACE ap_fifo port=a
#pragma HLS INTERFACE ap_fifo port=b
#pragma HLS INTERFACE ap_fifo port=c
#pragma HLS INTERFACE ap_fifo port=res
#pragma HLS ARRAY_RESHAPE variable=res complete dim=2
#pragma HLS ARRAY_RESHAPE variable=c complete dim=2
#pragma HLS ARRAY_RESHAPE variable=b complete dim=0
#pragma HLS ARRAY_RESHAPE variable=a complete dim=2
  ama::hw::matfma<ExactType, kRows, kCols>(a, b, c, res);
}
