/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#define kCols 3
#define kRows 3

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
void operations_top_sw(int selection, const float a[kRows][kCols],
                       const float b[kRows][kCols], const float c[kRows][kCols],
                       float res[kRows][kCols]);
