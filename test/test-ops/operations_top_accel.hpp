/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#define HW_COSIM

#pragma once

using ExactType = float;

#define kCols 16
#define kRows 16

void operations_top_accel(int selection, const ExactType a[kRows][kCols],
                    const ExactType b[kCols][kRows], const ExactType c[kRows][kRows],
                    ExactType res[kRows][kRows]);
