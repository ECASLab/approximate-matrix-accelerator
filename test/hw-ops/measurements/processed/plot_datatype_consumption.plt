#!/usr/bin/env gnuplot -p
############################################################
## Copyright 2022
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

set term svg size 400, 300
set output "plot_".msize."_".accel."_dtype_consumption.svg"

set xlabel "Datatype bit-width (bits)"
set ylabel "Relative consumption (ZYNQ 7z020)"
set y2label "Latency in clocks"
set y2tics nomirror
set ytics nomirror
set key left top

# dims bw min_lat avg_lat max_lat dsp lut bram ff
plot "consumption_".accel."_".msize."_dtypes.data" u 2:4 smooth unique w lp axis x1y2 title "Avg Latency", \
     "consumption_".accel."_".msize."_dtypes.data" u 2:6 smooth unique w lp title "DSPs",\
     "consumption_".accel."_".msize."_dtypes.data" u 2:7 smooth unique w lp title "LUTs",\
     "consumption_".accel."_".msize."_dtypes.data" u 2:8 smooth unique w lp title "BRAM",\
     "consumption_".accel."_".msize."_dtypes.data" u 2:9 smooth unique w lp title "FFs" 

