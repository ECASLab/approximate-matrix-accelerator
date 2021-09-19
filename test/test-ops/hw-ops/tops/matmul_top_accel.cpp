/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "../../../../includes/linear.hpp"
#include "matmac_top_accel.hpp"

void matmul_top_accel(const ExactType a[kRows][kCols],
                      const ExactType b[kCols][kRows],
                      ExactType res[kRows][kRows]){
    ama::hw::matmul<ExactType,kRows,kCols>(a, b, res);
}