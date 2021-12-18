############################################################
## Copyright 2021
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

# Set your custom C-flags here
# For example:
Q_ROWS ?= 12
Q_COLS ?= 12
Q_SEED ?= 10
Q_DATATYPE ?= 0
Q_WL ?= 8
Q_USE_HLS_MATH ?= 1
Q_USE_REG_UNROLLING ?= 0
CUSTOM_FLAGS+=-DROWS=$(Q_ROWS) -DCOLS=$(Q_COLS) -DSEED=$(Q_SEED) -DDATATYPE=$(Q_DATATYPE) -DWL=$(Q_WL) -DUSE_HLS_MATH=$(Q_USE_HLS_MATH) -DUSE_REG_UNROLLING=$(Q_USE_REG_UNROLLING)
export CUSTOM_FLAGS Q_COLS Q_ROWS Q_SEED Q_DATATYPE Q_WL Q_USE_HLS_MATH Q_USE_REG_UNROLLING
