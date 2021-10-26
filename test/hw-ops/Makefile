############################################################
## Copyright 2021
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

include helpers/coreops.mk
include helpers/help.mk

SYN_TOOL?=vivado_hls

# Define environment variables for the script
PROJECT_NAME=hls_project_$(TEST)_$(Q_kRows)_$(Q_kCols)
TOP_FUNCTION=$(TEST)_top_accel
SRC_FILES=$(wildcard tops/$(TOP_FUNCTION).cpp) $(wildcard tops/$(TOP_FUNCTION).hpp)
TB_FILE=testbench/$(TEST)_test.cpp
DIRECTIVE_FILE=directives/$(TEST).tcl

# Files for the reports
RPT_FILE=measurements/$(TEST)_$(Q_kRows)_$(Q_kCols).rpt
REPORT_FILE=measurements/$(TEST)_$(Q_kRows)_$(Q_kCols).xml
SIMULATION_FILE=measurements/$(TEST)_$(Q_kRows)_$(Q_kCols).log

SYNTHESIS_RPT=$(PROJECT_NAME)/solution/syn/report/$(TOP_FUNCTION)_csynth.rpt
SYNTHESIS_REPORT=$(PROJECT_NAME)/solution/syn/report/$(TOP_FUNCTION)_csynth.xml
SIMULATION_LOG=$(PROJECT_NAME)/solution/csim/report/$(TOP_FUNCTION)_csim.log

export PROJECT_NAME TOP_FUNCTION SRC_FILES TB_FILE DIRECTIVE_FILE

# --- Top rules ---
.PHONY: test clean help

# Test is the variable where the op is specified
test: $(TEST)_
	$(info "Constructing and testing $(TEST)")

# Get measurements
measure: $(RPT_FILE) $(REPORT_FILE) $(SIMULATION_FILE)
	$(info "Measurements taken. Please, find them in measurements/")

# Massive generation - Do not run in parallel
measure-all:
	mpirun bash helpers/measure-all.sh

# Extracts the errors and other useful data
extract-data:
	bash helpers/extract-errors.sh
	python3 helpers/extract-report.py

help:
	$(info $(HELP_MESSAGE))

clean:
	$(RM) -r hls_project_* *.log

# --- Auxiliar ---
# Run synthesis
%_:
	$(SYN_TOOL) -f script.tcl

# Run synthesis for the report
$(SYNTHESIS_RPT): $(TEST)_
	$(info "Simulation ran")

$(SYNTHESIS_REPORT): $(TEST)_
	$(info "Simulation ran")

$(SIMULATION_LOG): $(TEST)_
	$(info "Simulation ran")

# Copy files to finish the measurement
$(RPT_FILE): $(SYNTHESIS_RPT)
	cp -f $< $@
	
$(REPORT_FILE): $(SYNTHESIS_REPORT)
	cp -f $< $@

$(SIMULATION_FILE): $(SIMULATION_LOG)
	cp -f $< $@

