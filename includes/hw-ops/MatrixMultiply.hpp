/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "MatrixOperator.hpp"
#include "cores/matmul.hpp"

namespace ama {
namespace hw {
namespace operators {

using namespace ama::hw;

/**
 * Matrix operator for matrix multiplication
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
class MatrixMultiply : public MatrixOperator<T, M, N, ADD, MULT, NL> {
 public:
  /**
   * Execute the exact implementation for three-operand operators
   * The matrix multiplication in ap_fixed<> is better than the ap_int<>
   * without paying significant overhead.
   * It is constraint to MxN * NxM matrices
   * @param op_a input operand A
   * @param op_b input operand B
   * @param op_c output operand C
   */
  virtual void Execute(
      const T op_a[MatrixOperator<T, M, N, ADD, MULT, NL>::rows]
                  [MatrixOperator<T, M, N, ADD, MULT, NL>::columns],
      const T op_b[MatrixOperator<T, M, N, ADD, MULT, NL>::columns]
                  [MatrixOperator<T, M, N, ADD, MULT, NL>::rows],
      T op_c[MatrixOperator<T, M, N, ADD, MULT, NL>::rows]
            [MatrixOperator<T, M, N, ADD, MULT, NL>::rows]);

 private:
  ADD add_{};
  MULT mult_{};
  NL non_linearity_{};
};

template <typename T, int M, int N, class ADD, class MULT, class NL>
inline void MatrixMultiply<T, M, N, ADD, MULT, NL>::Execute(
    const T op_a[MatrixOperator<T, M, N, ADD, MULT, NL>::rows]
                [MatrixOperator<T, M, N, ADD, MULT, NL>::columns],
    const T op_b[MatrixOperator<T, M, N, ADD, MULT, NL>::columns]
                [MatrixOperator<T, M, N, ADD, MULT, NL>::rows],
    T op_c[MatrixOperator<T, M, N, ADD, MULT, NL>::rows]
          [MatrixOperator<T, M, N, ADD, MULT, NL>::rows]) {
ama_hw_matrix_mult_rows:
  for (int i = 0; i < M; ++i) {
  ama_hw_matrix_mult_cols:
    for (int j = 0; j < N; ++j) {
      T val{0};
    ama_hw_matrix_mult_reduce_mult:
      for (int k = 0; k < N; ++k) {
        val = add_(val, mult_(op_a[i][k], op_b[k][j]));
      }
      op_c[i][j] = non_linearity_(val);
    }
  }
}

} /* namespace operators */
} /* namespace hw */
} /* namespace ama */
