/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <iostream>
#include <ctime>

#include "../../includes/hw-fma/fma.hpp"
#include "fma_top_accel.hpp"

void fma_top_accel(const ExactType a[kRows][kCols], const ExactType b[kCols][kRows],
                const ExactType c[kRows][kRows], ExactType res[kRows][kRows]) {
  ama::hw::fma<ExactType, kRows, kCols>(a, b, c, res);
}
