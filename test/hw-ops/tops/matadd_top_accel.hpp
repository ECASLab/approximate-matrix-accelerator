/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "testbench.hpp"

/**
 * @brief Matrix add top
 * It calls the function to perform
 * @param a Matrix of MxN dimensions
 * @param b Matrix of MxN dimensions
 * @param res Matrix with the result
 */
void matadd_top_accel(ExactType a[ROWS][COLS], ExactType b[ROWS][COLS],
                      ExactType res[ROWS][COLS]);
