/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

/**
 * @example mathadamard_top_accel.cpp
 * Matrix hadamard example
 */

#include "linear.hpp"
#include "matadd_top_accel.hpp"

void mathadamard_top_accel(ExactType a[ROWS][COLS], ExactType b[ROWS][COLS],
                           ExactType res[ROWS][COLS]) {
  /* Hadamard can be implemented as an element-wise product */
  using Op = ama::hw::arithmetic::exact::Mult<ExactType>;
  auto engine =
      ama::hw::operators::MatrixElementWise<ExactType, ROWS, COLS, Op>{};
  engine.Execute(a, b, res);
}
