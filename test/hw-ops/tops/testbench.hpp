/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <ap_fixed.h>
#include <ap_int.h>

#define WL 8
/*
#ifndef DATATYPE 
#define DATATYPE "fixed"
using ExactType = ap_fixed<8, 0>;
#else 
#define DATATYPE "int"
using ExactType = ap_int<8>;
#endif 
*/

#ifndef ROWS
#define ROWS 12
#endif

#ifndef COLS
#define COLS 12
#endif

#ifndef SEED
#define SEED 10
#endif

//using ExactType = ap_fixed<WL, 0>;
using ExactType = ap_int<WL>;
