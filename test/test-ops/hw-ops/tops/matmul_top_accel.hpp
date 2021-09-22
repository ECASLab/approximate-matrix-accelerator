/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

using ExactType = float;

#ifndef kRows
#define kRows 12
#endif

#ifndef kCols
#define kCols 12
#endif

/**
 * @brief MAC top
 * It calls the function to perform
 * @param a Matrix of MxN dimensions
 * @param b Matrix of NxM dimensions
 * @param res Matrix with the result
 */
void matmul_top_accel(const ExactType a[kRows][kCols],
                      const ExactType b[kCols][kRows],
                      ExactType res[kRows][kRows]);
                      