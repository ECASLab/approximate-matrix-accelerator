/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#define HW_COSIM

#pragma once

using ExactType = float;

#define kCols 12
#define kRows 12

/**
 * @brief FMA accelerator top
 *
 * This function defines the MAC accelerator and determines the data type and
 * the dimensions sizes of the matrices.
 * It also calls the functions that MAC accumulator individually for testing
 * the functionality in the testbench
 * This top function is needed for template definition because is required in the synthesis 
 * time in HLS and it has to be well defined.
 * It also emulates the interfaces without any particular protocol,
 * unless needed
 * 
 *  It calls the functions to perform depending on the selection
 * @param selection Sorting
 * @param a Matrix of MxN dimensions
 * @param b Matrix of MxN dimensions
 * @param c Matrix of MxN dimensions
 * @param res Matrix with the result
 */
void operations_top_accel(int selection, const ExactType a[kRows][kCols],
                    const ExactType b[kCols][kRows], const ExactType c[kRows][kRows],
                    ExactType res[kRows][kRows]);
