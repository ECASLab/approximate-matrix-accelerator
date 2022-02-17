/*
 * Copyright 2022
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "MatrixOperator.hpp"
#include "cores/arithmetic-exact.hpp"

namespace ama {
namespace hw {
namespace operators {

using namespace ama::hw;

/**
 * Matrix operator for element-wise generic operation class
 * It defines the interface for any operator engine. It also defines
 * the matrix dimensions
 * @tparam T datatype to work with.
 * @tparam M rows of a matrix
 * @tparam N columns of a matrix
 * @tparam OP generic operator functor. It is required and it applies over the
 * two matrices
 */
template <typename T, int M, int N, class OP>
class MatrixElementWise : public MatrixOperator<T, M, N, OP> {
 public:
  /**
   * Execute the exact implementation for three-operand operators
   * @param op_a input operand A
   * @param op_b input operand B
   * @param op_c output operand C
   */
  virtual void Execute(const T op_a[MatrixOperator<T, M, N, OP>::rows]
                                   [MatrixOperator<T, M, N, OP>::columns],
                       const T op_b[MatrixOperator<T, M, N, OP>::rows]
                                   [MatrixOperator<T, M, N, OP>::columns],
                       T op_c[MatrixOperator<T, M, N, OP>::rows]
                             [MatrixOperator<T, M, N, OP>::columns]) override;

 private:
  OP operator_{};
};

template <typename T, int M, int N, class OP>
inline void MatrixElementWise<T, M, N, OP>::Execute(
    const T op_a[MatrixOperator<T, M, N, OP>::rows]
                [MatrixOperator<T, M, N, OP>::columns],
    const T op_b[MatrixOperator<T, M, N, OP>::rows]
                [MatrixOperator<T, M, N, OP>::columns],
    T op_c[MatrixOperator<T, M, N, OP>::rows]
          [MatrixOperator<T, M, N, OP>::columns]) {
ama_hw_matrix_ew_rows:
  for (int i = 0; i < M; ++i) {
  ama_hw_matrix_ew_cols:
    for (int j = 0; j < N; ++j) {
      op_c[i][j] = operator_(op_a[i][j], op_b[i][j]);
    }
  }
}

} /* namespace operators */
} /* namespace hw */
} /* namespace ama */
