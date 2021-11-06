/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <ap_fixed.h>
#include <ap_int.h>

/* For getting WL */

#ifndef ROWS
#define ROWS 12
#endif

#ifndef COLS
#define COLS 12
#endif

#ifndef SEED
#define SEED 10
#endif

#ifndef WL
#define WL 8
#endif 


#if DATATYPE == 0
using ExactType = ap_fixed<WL, 0>;
#elif DATATYPE == 1 
using ExactType = ap_int<WL>;
#else
#error Unknown datatype. Please, use 0 for fixed and 1 for int
#endif 

//using ExactType = ap_fixed<WL, 0>;
//using ExactType = ap_int<WL>;
