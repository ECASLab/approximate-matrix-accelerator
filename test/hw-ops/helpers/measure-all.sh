#!/bin/bash
############################################################
## Copyright 2021
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

let CID=${OMPI_COMM_WORLD_RANK:-0}
let SIZE=${OMPI_COMM_WORLD_SIZE:-1}

# Dim limits
MIN_Q_DIM=${MIN_Q_DIM:-2}
MAX_Q_DIM=${MAX_Q_DIM:-16}
STEP_Q_DIM=${STEP_Q_DIM:-2}

# Precision
MIN_Q_WL=${MIN_Q_WL:-4}
MAX_Q_WL=${MAX_Q_WL:-16}
STEP_Q_WL=${STEP_Q_WL:-2}

# Accelerators - Discretised because of Bash limitations in unrolling
ACCELS=${ACCELS:-"matfma"}

# Offsets
START_IDX=$((${CID}*${STEP_Q_WL}+${MIN_Q_WL}))
STEP_IDX=$((${STEP_Q_WL}*${SIZE}))

# Compute the boundaries in BitWidth
for i in $(seq ${MIN_Q_DIM} ${STEP_Q_DIM} ${MAX_Q_DIM});
do
  for accel in ${ACCELS};
  do
    for wl in $(seq ${START_IDX} ${STEP_IDX} ${MAX_Q_WL});
    do
      echo "[Measuring all]: Computing ${accel} with Dims ${i} and Precision ${wl} bits in processor ${CID}"
      Q_ROWS=${i} Q_COLS=${i} Q_WL=${wl} TEST=${accel} CUSTOM_FLAGS=-DOVERRIDE_TH make measure || echo "Failed executing make"
    done
  done
done
