#!/usr/bin/env gnuplot -p
############################################################
## Copyright 2022
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

set term svg size 500, 400
set output "plot_".accel."_dtype_performance.svg"

set xlabel "Datatype bit-width (bits)"
set ylabel "Performance (GMACs)"
set y2label "Design efficiency"
set y2tics nomirror
set ytics nomirror
set key right top

ops(x)=(x*x*x)
freq=100000000
max(w,v)=w>v?w:v
div=1000000000
peakperf=276

# dims bw min_lat avg_lat max_lat dsp lut bram ff
plot "consumption_".accel."_2_dtypes.data" u 2:((ops(2) * freq / $4) * floor(1 / max($6,$7)) / div) smooth unique w lp title "O = 2",\
     "consumption_".accel."_2_dtypes.data" u 2:((ops(2) * freq / $4) * floor(1 / max($6,$7)) / div / peakperf) smooth unique w p lt rgb "#FF000000" axis x1y2 notitle,\
     "consumption_".accel."_4_dtypes.data" u 2:((ops(4) * freq / $4) * floor(1 / max($6,$7)) / div) smooth unique w lp title "O = 4",\
     "consumption_".accel."_6_dtypes.data" u 2:((ops(6) * freq / $4) * floor(1 / max($6,$7)) / div) smooth unique w lp title "O = 6",\
     "consumption_".accel."_8_dtypes.data" u 2:((ops(8) * freq / $4) * floor(1 / max($6,$7)) / div) smooth unique w lp title "O = 8",\
     "consumption_".accel."_10_dtypes.data" u 2:((ops(10) * freq / $4) * floor(1 / max($6,$7)) / div) smooth unique w lp title "O = 10",\
     "consumption_".accel."_12_dtypes.data" u 2:((ops(12) * freq / $4) * floor(1 / max($6,$7)) / div) smooth unique w lp title "O = 12",\
     "consumption_".accel."_14_dtypes.data" u 2:((ops(14) * freq / $4) * floor(1 / max($6,$7)) / div) smooth unique w lp title "O = 14",\
     "consumption_".accel."_16_dtypes.data" u 2:((ops(16) * freq / $4) * floor(1 / max($6,$7)) / div) smooth unique w lp title "O = 16",\
     "consumption_".accel."_16_dtypes.data" u 2:((ops(16) * freq / $4) * floor(1 / max($6,$7)) / div / peakperf) smooth unique w p lt rgb "#FF000000" axis x1y2 notitle

