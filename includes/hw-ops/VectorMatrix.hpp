/*
 * Copyright 2022
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

namespace ama {
namespace hw {

/**
 * Begin of the metaprogramming loop
 * This struct will recurse until having a termination as a
 * specialisation.
 * @tparam N current iteration. In the first, it is equal to NT
 * @tparam NT total number of iterations
 * @tparam ENGINE class/module to iterate
 */
template <int N, int NT, class ENGINE>
struct ParallelMatrixOperator {
  /**
   * Execute method
   * It exposes the execution static to interact with the ENGINE. This is
   * intended to be for two-operand operations
   * FIXME: generalise for non-square matrices
   * @param op_a input a
   * @param op_b output
   */
  static void Execute(
      typename ENGINE::datatype op_a[NT * ENGINE::side][ENGINE::side],
      typename ENGINE::datatype op_b[NT * ENGINE::side][ENGINE::side]) {
#pragma HLS INLINE /* Important! Inlining the execution allows parallelism */
    /* Execute PE */
    ENGINE op{};
    op.Execute(&op_a[ENGINE::side * (N - 1)], &op_b[ENGINE::side * (N - 1)]);

    /* Continue Loop - The next i = i - 1 */
    ParallelMatrixOperator<(N - 1), NT, ENGINE>::Execute(op_a, op_b);
  }

  /**
   * Execute method
   * It exposes the execution static to interact with the ENGINE. This is
   * intended to be for three-operand operations
   * FIXME: generalise for non-square matrices
   * @param op_a input a
   * @param op_b input b
   * @param op_c output
   */
  static void Execute(
      typename ENGINE::datatype op_a[NT * ENGINE::side][ENGINE::side],
      typename ENGINE::datatype op_b[NT * ENGINE::side][ENGINE::side],
      typename ENGINE::datatype op_c[NT * ENGINE::side][ENGINE::side]) {
#pragma HLS INLINE /* Important! Inlining the execution allows parallelism */
    /* Execute PE */
    ENGINE op{};
    op.Execute(&op_a[ENGINE::side * (N - 1)], &op_b[ENGINE::side * (N - 1)],
               &op_c[ENGINE::side * (N - 1)]);

    /* Continue Loop - The next i = i - 1 */
    ParallelMatrixOperator<(N - 1), NT, ENGINE>::Execute(op_a, op_b, op_c);
  }

  /**
   * Execute method
   * It exposes the execution static to interact with the ENGINE. This is
   * intended to be for four-operand operations
   * FIXME: generalise for non-square matrices
   * @param op_a input a
   * @param op_b input b
   * @param op_c input c
   * @param op_d output
   */
  static void Execute(
      typename ENGINE::datatype op_a[NT * ENGINE::side][ENGINE::side],
      typename ENGINE::datatype op_b[NT * ENGINE::side][ENGINE::side],
      typename ENGINE::datatype op_c[NT * ENGINE::side][ENGINE::side],
      typename ENGINE::datatype op_d[NT * ENGINE::side][ENGINE::side]) {
#pragma HLS INLINE /* Important! Inlining the execution allows parallelism */
    /* Execute PE */
    ENGINE op{};
    op.Execute(&op_a[ENGINE::side * (N - 1)], &op_b[ENGINE::side * (N - 1)],
               &op_c[ENGINE::side * (N - 1)], &op_d[ENGINE::side * (N - 1)]);

    /* Continue Loop - The next i = i - 1 */
    ParallelMatrixOperator<(N - 1), NT, ENGINE>::Execute(op_a, op_b, op_c,
                                                         op_d);
  }
};

/**
 * End of the metaprogramming loop
 */
template <int NT, class ENGINE>
struct ParallelMatrixOperator<0, NT, ENGINE> {
  static void Execute(
      typename ENGINE::datatype op_a[NT * ENGINE::side][ENGINE::side],
      typename ENGINE::datatype op_b[NT * ENGINE::side][ENGINE::side]) {
#pragma HLS INLINE /* Important! Inlining the execution allows parallelism */
    /* Do Nothing (terminate loop) */
  }

  static void Execute(
      typename ENGINE::datatype op_a[NT * ENGINE::side][ENGINE::side],
      typename ENGINE::datatype op_b[NT * ENGINE::side][ENGINE::side],
      typename ENGINE::datatype op_c[NT * ENGINE::side][ENGINE::side]) {
#pragma HLS INLINE /* Important! Inlining the execution allows parallelism */
    /* Do Nothing (terminate loop) */
  }

  static void Execute(
      typename ENGINE::datatype op_a[NT * ENGINE::side][ENGINE::side],
      typename ENGINE::datatype op_b[NT * ENGINE::side][ENGINE::side],
      typename ENGINE::datatype op_c[NT * ENGINE::side][ENGINE::side],
      typename ENGINE::datatype op_d[NT * ENGINE::side][ENGINE::side]) {
#pragma HLS INLINE /* Important! Inlining the execution allows parallelism */
    /* Do Nothing (terminate loop) */
  }
};

} /* namespace hw */
} /* namespace ama */
