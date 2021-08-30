/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#define HW_COSIM

#pragma once

#define kCols 3
#define kRows 3

void operations_top_accel(int selection, const float a[kRows][kCols],
                    const float b[kRows][kCols], const float c[kRows][kCols],
                    float res[kRows][kCols]);
