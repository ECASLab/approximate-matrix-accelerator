/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#define HW_COSIM

#pragma once

#define kCols 5
#define kRows 4

void operations_top_accel(int selection, const float a[kRows][kCols],
                    const float b[kCols][kRows], const float c[kRows][kRows],
                    float res[kRows][kRows]);
