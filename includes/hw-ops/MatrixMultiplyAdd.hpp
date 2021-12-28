/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "MatrixOperator.hpp"
#include "cores/matfma.hpp"

namespace ama {
namespace hw {
namespace operators {

using namespace ama::hw;

/**
 * Matrix operator for matrix multiply-add
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
class MatrixMultiplyAdd : public MatrixOperator<T, M, N, ADD, MULT, NL> {
 public:
  /**
   * Execute the exact implementation for three-operand operators
   * @param op_a input operand A to multiply with
   * @param op_b input operand B to multiply with
   * @param op_c input operand C to add with
   * @param op_d output operand D
   */
  virtual void Execute(
      const T op_a[MatrixOperator<T, M, N, ADD, MULT, NL>::rows]
                  [MatrixOperator<T, M, N, ADD, MULT, NL>::columns],
      const T op_b[MatrixOperator<T, M, N, ADD, MULT, NL>::rows]
                  [MatrixOperator<T, M, N, ADD, MULT, NL>::columns],
      const T op_c[MatrixOperator<T, M, N, ADD, MULT, NL>::rows]
                  [MatrixOperator<T, M, N, ADD, MULT, NL>::columns],  
      T op_d[MatrixOperator<T, M, N, ADD, MULT, NL>::rows]
            [MatrixOperator<T, M, N, ADD, MULT, NL>::columns]) override;

 private:
  ADD add_{};
  MULT mult_{};
  NL non_linearity_{};
};

template <typename T, int M, int N, class ADD, class MULT, class NL>
void MatrixMultiplyAdd<T, M, N, ADD, MULT, NL>::Execute(
    const T op_a[MatrixOperator<T, M, N, ADD, MULT, NL>::rows]
                [MatrixOperator<T, M, N, ADD, MULT, NL>::columns],
    const T op_b[MatrixOperator<T, M, N, ADD, MULT, NL>::rows]
                [MatrixOperator<T, M, N, ADD, MULT, NL>::columns],
    const T op_c[MatrixOperator<T, M, N, ADD, MULT, NL>::rows]
                  [MatrixOperator<T, M, N, ADD, MULT, NL>::columns],  
      T op_d[MatrixOperator<T, M, N, ADD, MULT, NL>::rows]
            [MatrixOperator<T, M, N, ADD, MULT, NL>::columns]) {
  core::matfma<T, M, N>(op_a, op_b, op_c, op_d);
}

} /* namespace operators */
} /* namespace hw */
} /* namespace ama */
