#!/usr/bin/env gnuplot -p
############################################################
## Copyright 2022
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

set term svg size 640, 480
set output "plot_hist_datatypes_".accel."_".msize.".svg"

set xlabel "Normalised Error (0 to 1)"
set ylabel "Scaled occurence (1/max)"

# hist_${HIST_BINS}_${HIST_PERC}_${Q_DIM}_${Q_WL}_${ACCEL}.data
# Type Kernel_Size Min Max Mean StdDev Variance
plot "norm_hist_500_30%_".msize."_4_".accel.".data" u ($0*0.3/500):($1) w l title "W = 4", \
     "norm_hist_500_30%_".msize."_6_".accel.".data" u ($0*0.3/500):($1) w l title "W = 6", \
     "norm_hist_500_30%_".msize."_8_".accel.".data" u ($0*0.3/500):($1) w l title "W = 8", \
     "norm_hist_500_30%_".msize."_10_".accel.".data" u ($0*0.3/500):($1) w l title "W = 10", \
     "norm_hist_500_30%_".msize."_12_".accel.".data" u ($0*0.3/500):($1) w l title "W = 12", \
     "norm_hist_500_30%_".msize."_14_".accel.".data" u ($0*0.3/500):($1) w l title "W = 14", \
     "norm_hist_500_30%_".msize."_16_".accel.".data" u ($0*0.3/500):($1) w l title "W = 16"
