############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
set_directive_top -name $::env(TOP_FUNCTION) "$::env(TOP_FUNCTION)"

# Register Mappings
set_directive_array_partition -type complete -dim 0 "matfma_top_accel" a
set_directive_array_partition -type complete -dim 0 "matfma_top_accel" b
set_directive_array_partition -type complete -dim 0 "matfma_top_accel" res

# Unroll and pipeline
set_directive_pipeline "MatrixMultiplyAdd<T, M, N, ADD, MULT, NL>::Execute/ama_hw_matrix_fma_rows"

# No-inline
set_directive_inline -off "MatrixMultiplyAdd<T, M, N, ADD, MULT, NL>::Execute"
