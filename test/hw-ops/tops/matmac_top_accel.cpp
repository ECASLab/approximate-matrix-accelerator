/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "matmac_top_accel.hpp"

#include "linear.hpp"

void matmac_top_accel(const ExactType a[ROWS][COLS],
                      const ExactType b[COLS][ROWS],
                      const ExactType c[ROWS][ROWS],
                      ExactType res[ROWS][ROWS]) {
  ama::hw::core::matmac<ExactType, ROWS, COLS>(a, b, c, res);
}
