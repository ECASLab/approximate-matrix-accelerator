/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

/**
 * @example vecfma_top_accel.cpp
 * Vectorised FMA example
 */

#include "vecfma_top_accel.hpp"

#include "linear.hpp"

void vecfma_top_accel(ExactType a[ACCEL * ROWS][ROWS],
                      ExactType b[ACCEL * ROWS][ROWS],
                      ExactType c[ACCEL * ROWS][ROWS],
                      ExactType res[ACCEL * ROWS][ROWS]) {
  using Engine = ama::hw::operators::MatrixMultiplyAdd<ExactType, ROWS, ROWS>;
  ama::hw::ParallelMatrixOperator<ACCEL, ACCEL, Engine>::Execute(a, b, c, res);
}
