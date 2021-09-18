/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "../../includes/operations.hpp"
#include "operations_top_accel.hpp"

void operations_top_accel(int selection, const ExactType a[kRows][kCols],
                    const ExactType b[kCols][kRows], const ExactType c[kRows][kRows],
                    ExactType res[kRows][kRows]){
  switch (selection) {
    case 0:
      ama::hw::matadd<ExactType, kRows, kRows>(c, c, res);
      break;
    case 1:
      ama::hw::matmul<ExactType, kRows, kCols>(a, b, res);
      break;
    case 2:
      ama::hw::matmac<ExactType, kRows, kCols>(a, b, c, res);
      break;
  }
}
