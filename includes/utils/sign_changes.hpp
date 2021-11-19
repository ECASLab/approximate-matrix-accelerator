/*
 * Copyright 2021
 * Author: Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <iostream>

namespace ama{
namespace utils{

/**
 * @brief Results test comparison
 * @tparam TH Data type for hardware implementation
 * @tparam TS Data type for software implementation
 * @tparam M Rows size of matrices
 * @tparam N Cols size of matrices
 * @param hw_result Left Matrix to compare
 * It represents the result of hardware
 * implementation
 * @param sw_result Right Matrix to compare
 * It represents the result of software
 * implementation
 */
template <typename TH, typename TS, int M, int N>
void sign_changes(const TH hw_result[M][N], const TS sw_result[M][N]){
    TS tmp = 0;
    std::cout << std::setprecision(6) << std::fixed;
    for(int i = 0; i < M; ++i){
        for(int j = 0; j < N; ++j){
            tmp = static_cast<TS>(hw_result[i][j]) * sw_result[i][j];
            if(tmp < 0){
                std::cout << "Sign changes in indices " << '[' << i << ']' 
                          << '[' << j << ']' << " hw_value " << static_cast<TS>(hw_result[i][j])
                          << ", " << "sw_value " <<  sw_result[i][j] << std::endl;
            }
        }
    }
}
}
}