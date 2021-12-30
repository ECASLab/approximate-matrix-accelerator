############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
set_directive_top -name $::env(TOP_FUNCTION) "$::env(TOP_FUNCTION)"

# Register Mappings
set_directive_array_partition -type complete -dim 0 "matmul_top_accel" a
set_directive_array_partition -type complete -dim 0 "matmul_top_accel" b
set_directive_array_partition -type complete -dim 0 "matmul_top_accel" res

# Unroll and pipeline
set_directive_pipeline "MatrixMultiply<T, M, N, ADD, MULT, NL>::Execute/ama_hw_matrix_mult_rows"
set_directive_unroll "MatrixMultiply<T, M, N, ADD, MULT, NL>::Execute/ama_hw_matrix_mult_reduce"
set_directive_loop_flatten -off "MatrixMultiply<T, M, N, ADD, MULT, NL>::Execute/ama_hw_matrix_mult_rows"

# No-inline
set_directive_inline -off "MatrixMultiply<T, M, N, ADD, MULT, NL>::Execute"
