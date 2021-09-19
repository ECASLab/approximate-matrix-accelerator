/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "../../includes/linear.hpp"
#include "matfma_top_accel.hpp"

void matfma_top_accel(const ExactType a[kRows][kCols], const ExactType b[kCols][kRows],
                const ExactType c[kRows][kRows], ExactType res[kRows][kRows]) {
  ama::hw::matfma<ExactType, kRows, kCols>(a, b, c, res);
}
