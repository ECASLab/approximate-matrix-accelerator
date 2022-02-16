/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

namespace ama {
namespace hw {
namespace arithmetic {
namespace exact {

/**
 * These are the exact versions for the operations
 * This are baseline implementations
 */

template <typename T>
class Mult {
 public:
  T operator()(const T lhs, const T rhs) {
#pragma HLS INLINE
    return lhs * rhs;
  }
};

template <typename T>
class Add {
 public:
  T operator()(const T lhs, const T rhs) {
#pragma HLS INLINE
    return lhs + rhs;
  }
};

template <typename T>
class PassThru {
 public:
  T operator()(const T lhs) {
#pragma HLS INLINE
    return lhs;
  }
};

}  // namespace exact
}  // namespace arithmetic
}  // namespace hw
}  // namespace ama
