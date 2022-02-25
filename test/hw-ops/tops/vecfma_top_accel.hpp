/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "testbench.hpp"

/**
 * @brief Vectorised FMA accelerator top
 *
 * This function defines the FMA accelerator and determines the data type and
 * the dimensions sizes of the matrices in a vectorised fashion.
 * This top function is needed for template definition because is required in
 * the synthesis time in HLS and it has to be well defined. It also emulates the
 * interfaces without any particular protocol, unless needed
 *
 * @param a Matrix of MxM dimensions
 * @param b Matrix of MxM dimensions
 * @param c Matrix of MxM dimensions
 * @param res Matrix with the result
 */
void vecfma_top_accel(ExactType a[ACCEL * ROWS][ROWS],
                      ExactType b[ACCEL * ROWS][ROWS],
                      ExactType c[ACCEL * ROWS][ROWS],
                      ExactType res[ACCEL * ROWS][ROWS]);
