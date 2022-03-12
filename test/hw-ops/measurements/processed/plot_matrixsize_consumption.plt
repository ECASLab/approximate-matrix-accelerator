#!/usr/bin/env gnuplot -p
############################################################
## Copyright 2022
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

set term svg size 640, 480
set output "plot_".dt."_".accel."_dtype_consumption.svg"

set xlabel "Matrix size (NxN)"
set ylabel "Relative consumption (Avnet Zedboard - ZYNQ 7z020)"
set y2label "Latency in clocks"
set y2tics nomirror
set ytics nomirror
set key left top

# dims bw min_lat avg_lat max_lat dsp lut bram ff
plot "consumption_".accel."_".dt."_sizes.data" u 1:4 smooth unique w lp axis x1y2 title "Avg Latency", \
     "consumption_".accel."_".dt."_sizes.data" u 1:6 smooth unique w lp title "DSPs",\
     "consumption_".accel."_".dt."_sizes.data" u 1:7 smooth unique w lp title "LUTs",\
     "consumption_".accel."_".dt."_sizes.data" u 1:8 smooth unique w lp title "BRAM",\
     "consumption_".accel."_".dt."_sizes.data" u 1:9 smooth unique w lp title "FFs" 

