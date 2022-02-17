/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <ap_fixed.h>
#include <ap_int.h>

#ifndef ROWS
#define ROWS 8
#endif

#ifndef COLS
#define COLS 8
#endif

#ifndef SEED
#define SEED 10
#endif

#ifndef ACCEL
#define ACCEL 3
#endif

#ifndef WL
#define WL 8
#endif 


#if DATATYPE == 0
using ExactType = ap_fixed<WL+1, 1, AP_RND>;
#elif DATATYPE == 1 
using ExactType = ap_int<WL+1>;
#else
#error Unknown datatype. Please, use 0 for fixed and 1 for int
#endif 
