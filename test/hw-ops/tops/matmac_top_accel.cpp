/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "linear.hpp"
#include "matmac_top_accel.hpp"

void matmac_top_accel(const ExactType a[ROWS][COLS],
                      const ExactType b[COLS][ROWS],
                      const ExactType c[ROWS][ROWS],
                      ExactType res[ROWS][ROWS]) {
  ama::hw::matmac<ExactType, ROWS, COLS>(a, b, c, res);
}
