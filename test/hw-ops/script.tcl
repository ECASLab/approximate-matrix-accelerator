############################################################
## Copyright 2021
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################
open_project $::env(PROJECT_NAME)
set_top $::env(TOP_FUNCTION)
add_files $::env(SRC_FILES) -cflags "-std=c++11 -I../../includes $::env(CUSTOM_FLAGS)"
add_files -tb $::env(TB_FILE) -cflags "-std=c++11 -Wno-unknown-pragmas -I../../includes -I./tops $::env(CUSTOM_FLAGS)"
open_solution "solution"
set_part {xc7z020clg484-1}
create_clock -period 10 -name default
source "$::env(DIRECTIVE_FILE)"
csim_design -clean
#csynth_design
#cosim_design
exit
