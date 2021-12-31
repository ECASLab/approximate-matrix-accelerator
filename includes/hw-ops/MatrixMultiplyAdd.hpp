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
   * Hard-wired to be ap_fixed provided that it is the most efficient
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
  const T alpha = 1.f / (2 * M);

ama_hw_matrix_fma_rows:
  for (int i = 0; i < M; ++i) {
  ama_hw_matrix_fma_cols:
    for (int j = 0; j < N; ++j) {
      T val = mult_(op_c[i][j], alpha);
    ama_hw_matrix_fma_reduce_mult:
      for (int k = 0; k < N; ++k) {
        val = add_(val, mult_(mult_(op_a[i][k], alpha), op_b[k][j]));
      }
      op_d[i][j] = non_linearity_(val);
    }
  }
}

} /* namespace operators */
} /* namespace hw */
} /* namespace ama */
