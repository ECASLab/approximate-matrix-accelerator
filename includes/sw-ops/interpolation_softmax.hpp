/*
 * Copyright 2022
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 * Author: Fabricio Elizondo Fernandez <faelizondo@estudiantec.cr>
 */

#pragma once

#include <cmath>

namespace ama{
namespace sw{
namespace lut{

template<typename T, int S, int BEGIN, int END>
void exp_table(T lut[S]){
  static const float step = (float)std::abs(END - BEGIN) / (float)S;

  for(int i = 0; i < S; ++i){
    float x = BEGIN + i * step;
    lut[i] = T{std::exp(x)};
  }    
}

} /* namespace lut */

namespace interpolation{

template<typename T, int S = 128, int BEGIN = -14, int END = 2>
T linear(const T x) {
  const T step = T{(float)S / (float)std::abs(END - BEGIN)};
  int i_upper{0}, i_lower{0};
  bool cond{false};
  T res{0}; 

  T lut[S];
  lut::exp_table<T, S, BEGIN, END>(lut);

  i_lower = (T{x} - T{BEGIN}) * step;
  i_lower = i_lower <= 0 ? 0 : i_lower;
  i_lower = i_lower >= S ? S - 1 : i_lower;

  i_upper = i_lower + 1;
  cond = i_upper == S ? true : cond;
  i_lower = cond ? S - 2 : i_lower;
  i_upper = cond ? S - 1 : i_upper; 


  const T x_lower = T{BEGIN} + (i_lower / step);
  const T x_upper = T{BEGIN} + (i_upper / step);  
  res = lut[i_lower] + ((lut[i_upper] - lut[i_lower]) / 
        (x_upper - x_lower)) * (x - x_lower);  

  return res;
}

template<typename T, int S = 128, int BEGIN = -14, int END = 2>
T quadratic(const T x) {
  const T step = T{(float)S / (float)std::abs(END - BEGIN)};
  int i_upper{0}, i_medium{0}, i_lower{0};
  bool zero_cond{false}, limit_cond{false};
  T res{0}, b_0{0}, b_1{0}, b_2{0};

  T lut[S];
  lut::exp_table<T, S, BEGIN, END>(lut);

  i_medium = (T{x} - T{BEGIN}) * step;
  i_medium = i_medium <= 0 ? 0 : i_medium;
  i_medium = i_medium >= S ? S - 1 : i_medium;

  i_upper = i_medium + 1;
  i_lower = i_medium - 1;
  limit_cond = i_upper == S ? true : limit_cond;
  zero_cond = i_lower < 0 ? true : zero_cond;
  i_upper = limit_cond ? i_medium : i_upper;
  i_medium = limit_cond ? i_upper - 1 : i_medium;
  i_lower = limit_cond ? i_upper - 2 : i_lower;
  i_lower = zero_cond ? 0 : i_lower;
  i_medium = zero_cond ? i_lower + 1 : i_medium;
  i_upper = zero_cond ? i_lower + 2 : i_upper;

  const T x_lower = T{BEGIN} + (i_lower / step);
  const T x_medium = T{BEGIN} + (i_medium / step);
  const T x_upper = T{BEGIN} + (i_upper / step);
  
  b_0 = lut[i_lower];
  b_1 = (lut[i_medium] - lut[i_lower]) / 
        (x_medium - x_lower);
  b_2 = (((lut[i_upper] - lut[i_medium]) / (x_upper - x_medium)) - 
        ((lut[i_medium] - lut[i_lower]) / (x_medium - x_lower))) / 
        (x_upper - x_lower);

  res = b_0 + b_1 * (x - x_lower) + b_2 * (x - x_lower) * (x - x_medium);
  return res;
}

} /* namespace interpolation */

namespace core{

template<typename T, int K, bool OP>
void interpolation_softmax(const T z[K], T res[K]) {
  T exp_sum{0};

  for (int i = 0; i < K; ++i) {
    res[i] = OP ? interpolation::linear<T>(z[i]) : interpolation::quadratic<T>(z[i]);
    exp_sum += res[i];
  }

  for (int i = 0; i < K; ++i) {
    res[i] /= exp_sum;
  }
}

} /* namespace core */
} /* namespace sw */
} /* namespace ama */
