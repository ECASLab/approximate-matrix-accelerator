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
T linear(const T x, const bool op) {
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
  cond = i_upper >= S ? true : cond;
  i_lower = cond ? S - 2 : i_lower;
  i_upper = cond ? S - 1 : i_upper; 

  if (op){
    res = (lut[i_lower] + lut[i_upper]) * T{0.5f};    
  }
  else{
    const T x_lower = T{BEGIN} + (i_lower / step);
    const T x_upper = T{BEGIN} + (i_upper / step);  
    res = lut[i_lower] + ((lut[i_upper] - lut[i_lower]) / 
          (x_upper - x_lower)) * (x - x_lower);  
  }
  
  return res;
}

} /* namespace interpolation */
} /* namespace sw */
} /* namespace ama */
