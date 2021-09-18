/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

using ExactType = float;

#define kRows 12
#define kCols 12

/**
 * @brief Fused Multiply-Add test
 * It calls the function to perform
 * @param a Matrix of MxN dimensions
 * @param b Matrix of MxN dimensions
 * @param c Matrix of MxN dimensions
 * @param res Matrix with the result
 */
void fma_top_sw(const ExactType a[kRows][kCols], const ExactType b[kCols][kRows],
                const ExactType c[kRows][kRows], ExactType res[kRows][kRows]);
