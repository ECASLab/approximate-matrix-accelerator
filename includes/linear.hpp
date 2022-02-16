/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

/* Hardware ops */
#include "hw-ops/cores/matadd.hpp"
#include "hw-ops/cores/matfma.hpp"
#include "hw-ops/cores/matmac.hpp"
#include "hw-ops/cores/matmul.hpp"

/* Interfaces */
#include "hw-ops/MatrixOperators.hpp"

/* Software ops */
#include "sw-ops/matadd.hpp"
#include "sw-ops/matfma.hpp"
#include "sw-ops/matmac.hpp"
#include "sw-ops/matmul.hpp"

/* Utils */
#include "utils/compare_results.hpp"
#include "utils/print_matrices.hpp"
#include "utils/sign_changes.hpp"

#include "version.hpp"
