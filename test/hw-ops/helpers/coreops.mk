############################################################
## Copyright 2021
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

# Set your custom C-flags here
# For example:
Q_kRows ?= 12
Q_kCols ?= 12
Q_kSeed ?= 10
Q_USE_HLS_MATH ?= 1
Q_USE_REG_UNROLLING ?= 0
CUSTOM_FLAGS+=-DkRows=$(Q_kRows) -DkCols=$(Q_kCols) -Dkseed=$(Q_kSeed) -DUSE_HLS_MATH=$(Q_USE_HLS_MATH) -DUSE_REG_UNROLLING=$(Q_USE_REG_UNROLLING)
export CUSTOM_FLAGS Q_kCols Q_kRows Q_kSeed Q_USE_HLS_MATH Q_USE_REG_UNROLLING
