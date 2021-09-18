/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

using ExactType = float;

#define kCols 12
#define kRows 12

/**
 * @brief FMA accelerator top
 *
 * This function defines the FMA accelerator and determines the data type and
 * the dimensions sizes of the matrices.
 * This top function is needed for template definition because is required in the synthesis 
 * time in HLS and it has to be well defined.
 * It also emulates the interfaces without any particular protocol,
 * unless needed
 * 
 * @param a Matrix of MxN dimensions
 * @param b Matrix of MxN dimensions
 * @param c Matrix of MxN dimensions
 * @param res Matrix with the result
 */
void fma_top_accel(const ExactType a[kRows][kCols],
                    const ExactType b[kCols][kRows], const ExactType c[kRows][kRows],
                    ExactType res[kRows][kRows]);
