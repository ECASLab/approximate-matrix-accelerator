/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "cores/arithmetic-exact.hpp"

namespace ama {
namespace hw {

/**
 * Matrix operator template class
 * It defines the interface for any operator engine. It also defines
 * the matrix dimensions
 * @tparam T datatype to work with.
 * @tparam M rows of a matrix
 * @tparam N columns of a matrix
 * @tparam ADD add functor. Defaults to the exact version
 * @tparam MULT mult functor. Defaults to the exact version
 * @tparam NL non-linear functor. Defaults to the pass-thru
 */
template <typename T, int M, int N, class ADD = arithmetic::exact::Add<T>,
          class MULT = arithmetic::exact::Mult<T>,
          class NL = arithmetic::exact::PassThru<T>>
class MatrixOperator {
 public:
  /*
   * Define some useful variables for implementation purposes
   */
  static const int rows = M;
  static const int columns = N;
  static const int elements = rows * columns;
};

} /* namespace hw */
} /* namespace ama */
