#!/bin/bash
############################################################
## Copyright 2022
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

# dims bw min_lat avg_lat max_lat dsp lut bram ff

# Join the consumptions for datatypes
ACCELS="matfma"
for msize in $(seq 2 2 16);
do
for acc in ${ACCELS};
do
  FILE="${acc}-report.data"
  awk "{if (\$1 == ${msize}) print \$0}" ${FILE} > "consumption_${acc}_${msize}_dtypes.data"
  gnuplot -e "accel='${acc}';msize='${msize}'" plot_datatype_consumption.plt
done
done
gnuplot -e "accel='${acc}';msize='${msize}'" plot_datatype_performance.plt
gnuplot -e "accel='${acc}';msize='${msize}'" plot_datatype_efficiency.plt

# Join the consumptions for matrix sizes
DT=8
ACCELS="matfma"
for acc in ${ACCELS};
do
  FILE="${acc}-report.data"
  awk "{if (\$2 == ${DT}) print \$0}" ${FILE} > "consumption_${acc}_${DT}_sizes.data"
  gnuplot -e "accel='${acc}';dt=${DT}" plot_matrixsize_consumption.plt
done

