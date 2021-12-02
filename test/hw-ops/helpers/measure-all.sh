#!/bin/bash
############################################################
## Copyright 2021
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

let CID=${OMPI_COMM_WORLD_RANK:-0}
let SIZE=${OMPI_COMM_WORLD_SIZE:-1}

# Q_BW limits
MIN_Q_DIM=${MIN_Q_DIM:-2}
MAX_Q_DIM=${MAX_Q_DIM:-16}
STEP=${STEP_Q_DIM:-2}

# Accelerators - Discretised because of Bash limitations in unrolling
ACCELS=${ACCELS:-"matadd matmac matmul matfma"}

# Offsets
START_IDX=$((${CID}*${STEP}+${MIN_Q_DIM}))
STEP_IDX=$((${STEP}*${SIZE}))

# Compute the boundaries in BitWidth
for i in $(seq ${START_IDX} ${STEP_IDX} ${MAX_Q_DIM});
do
  for accel in ${ACCELS};
  do
    echo "[Measuring all]: Computing ${accel} with Dims ${i} in processor ${CID}"
    Q_ROWS=${i} Q_COLS=${i} TEST=${accel} CUSTOM_FLAGS=-DOVERRIDE_TH make measure || echo "Failed executing make"
  done
done
