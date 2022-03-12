#!/bin/bash

# Compute the maximum and then, divide
for file in $(ls hist_*);
do
  # Normalising
  echo "Normalising: ${file}"
  MAX=$(awk 'NR==1{max = $1 + 0; next} {if ($1 > max) max = $1;} END {print max}' ${file})
  awk "{print \$1/${MAX}}" ${file} > norm_${file}
done

# Compute the histograms for every accel and image
MIN_Q_DIM=${MIN_Q_DIM:-2}
MAX_Q_DIM=${MAX_Q_DIM:-16}
STEP_Q_DIM=${STEP_Q_DIM:-2}
MSIZES=$(seq ${MIN_Q_DIM} ${STEP_Q_DIM} ${MAX_Q_DIM})
ACCELS="matfma"
for msize in ${MSIZES};
do
  for acc in ${ACCELS};
  do
    gnuplot -e "accel='${acc}';msize='${msize}'" plot_hist_datatypes.plt
  done
done

