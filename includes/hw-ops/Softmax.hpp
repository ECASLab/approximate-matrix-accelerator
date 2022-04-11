/*
 * Copyright 2022
 * Author: Fabricio Elizondo Fernandez <faelizondo@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "MatrixOperator.hpp"

#pragma once

namespace ama{
namespace hw{
namespace nl{

template <typename T, int K, class OP>
void map(const T z[K], T res[K], OP unary_op){

    for (int i = 0; i < K; ++i){
        res[i] = unary_op(z[i]);
    }
}

template <typename T, int K, class OP>
T reduce(const T op_a, const T op_b, OP binary_op){

    return binary_op(op_a, op_b);
}

template<typename T, int K, class EXP = arithmetic::exact::PassThru<T>,
         class SUM = arithmetic::exact::PassThru<T>,
         class MUL = arithmetic::exact::PassThru<T>>
void softmax(const T z[K], T res[K]){
    EXP exp_op{};
    SUM sum_op{};
    T res_map[K]{};
    T sum_exp{0.};

    nl::map<T,K,EXP>(z[K], res_map[K], exp_op);

    for (int i = 0; i < K; i += 2){
        sum_exp += nl::reduce<T,K,SUM>(res_map[i], res_map[++i], sum_op)
    }

    auto exp_inv = T{1.} / sum_exp;
    MUL mul_op{exp_inv};
    nl::map<T,K,MUL>(res_map[k], res[k], mul_op);
}


} // namespace nl
} // namespace hw
} // namespace ama