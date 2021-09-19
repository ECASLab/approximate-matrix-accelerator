############################################################
## Copyright 2021
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

# Set your custom C-flags here
# For example:
Q_kRows ?= 12
Q_kCols ?= 12
CUSTOM_FLAGS+=-DkRows=$(Q_kRows) -DkCols=$(Q_kCols)
export CUSTOM_FLAGS Q_kCols Q_kRows
