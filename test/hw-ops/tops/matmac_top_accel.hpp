/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "testbench.hpp"

/**
 * @brief MAC top
 * It calls the function to perform
 * @param a Matrix of MxN dimensions
 * @param b Matrix of NxM dimensions
 * @param C Matrix of MxM dimensions
 * @param res Matrix with the result
 */
void matmac_top_accel(const ExactType a[ROWS][COLS],
                      const ExactType b[COLS][ROWS],
                      const ExactType c[ROWS][ROWS],
                      ExactType res[ROWS][ROWS]);
