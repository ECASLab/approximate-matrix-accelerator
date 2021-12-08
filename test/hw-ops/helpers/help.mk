############################################################
## Copyright 2021
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

FOPS=$(wildcard tops/*.cpp)
POPS=$(FOPS:tops/%=%)
OPS=$(POPS:_top_accel.cpp=)

define HELP_MESSAGE
------------------------------------------
-- Testing system for the HW Operations --
------------------------------------------
Usage: TEST=matadd make test

Environment variables:
- TEST: name of the operation. Possible values:
	{$(OPS)}
	Used in: test, measure

Targets:
- all: synthesise and runs the test for the given operation [descouraged]
- test: synthesises and runs the simulation for the given operation
- measure: synthesises, runs and extracts the logs for measurement
- measure-all: runs all the synthesis and simulations
- extract-data: cleans the logs, recompiling just the useful information

CoreOps modifiers:
- Q_COLS: cols of each matrix. Def: $(Q_COLS)
- Q_ROWS: rows of each matrix. Def: $(Q_ROWS)
- Q_SEED: seed uses for generating random numbers. Def: $(Q_SEED)
- Q_DATATYPE: datatype of hardware matrices. Def: $(Q_DATATYPE)
- Q_WL: word length of datatype. Def: $(Q_WL) 
- Q_USE_HLS_MATH: enables the hls math library. Def: $(Q_USE_HLS_MATH)
- Q_USE_REG_UNROLLING: selects which scenario use in matfma operation. Def: $(Q_USE_REG_UNROLLING)
------------------------------------------
endef
