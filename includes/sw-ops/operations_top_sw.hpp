/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

using ExactType = float;

#define kRows 4
#define kCols 3

/**
 * @brief Matrix multiplication test
 * It calls the functions to perform
 * depending on the selection
 * @param selection Sorting
 * @param a Matrix of MxN dimensions
 * @param b Matrix of MxN dimensions
 * @param c Matrix of MxN dimensions
 * @param res Matrix with the result
 */
void operations_top_sw(int selection, const ExactType a[kRows][kCols],
                       const ExactType b[kCols][kRows], const ExactType c[kRows][kRows],
                       ExactType res[kRows][kRows]);
