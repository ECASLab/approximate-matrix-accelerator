/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

/* Hardware ops */
#include "hw-fma/matfma.hpp"
#include "hw-ops/matadd.hpp"
#include "hw-ops/matmac.hpp"
#include "hw-ops/matmul.hpp"

/* Software ops */
#include "sw-fma/matfma.hpp"
#include "sw-fma/matfma_top_sw.hpp"
#include "sw-ops/matadd.hpp"
#include "sw-ops/matmac.hpp"
#include "sw-ops/matmul.hpp"

/* Utils */
#include "utils/compare_results.hpp"
#include "utils/print_matrices.hpp"
