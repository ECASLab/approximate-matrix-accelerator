############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
set_directive_top -name $::env(TOP_FUNCTION) "$::env(TOP_FUNCTION)"

# Register Mappings
set_directive_array_partition -type complete -dim 0 "mathadamard_top_accel" a
set_directive_array_partition -type complete -dim 0 "mathadamard_top_accel" b
set_directive_array_partition -type complete -dim 0 "mathadamard_top_accel" res

# Unroll
set_directive_unroll "MatrixElementWise<T, M, N, OP>::Execute/ama_hw_matrix_ew_rows"
set_directive_unroll "MatrixElementWise<T, M, N, OP>::Execute/ama_hw_matrix_ew_cols"

# No-inline
set_directive_inline -off "MatrixElementWise<T, M, N, OP>::Execute"
