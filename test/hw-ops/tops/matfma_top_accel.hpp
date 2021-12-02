/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "testbench.hpp"

/**
 * @brief FMA accelerator top
 *
 * This function defines the FMA accelerator and determines the data type and
 * the dimensions sizes of the matrices.
 * This top function is needed for template definition because is required in
 * the synthesis time in HLS and it has to be well defined. It also emulates the
 * interfaces without any particular protocol, unless needed
 *
 * @param a Matrix of MxN dimensions
 * @param b Matrix of MxN dimensions
 * @param c Matrix of MxN dimensions
 * @param res Matrix with the result
 */
void matfma_top_accel(const ExactType a[ROWS][COLS],
                      const ExactType b[COLS][ROWS],
                      const ExactType c[ROWS][ROWS],
                      ExactType res[ROWS][ROWS]);
