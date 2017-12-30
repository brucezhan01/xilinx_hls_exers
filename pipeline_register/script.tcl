open_project pipeline_register_prj
set_top kernel_top
add_files kernel_top.cpp
add_files -tb main.cpp

open_solution "solution0"
set_part {xcku115-flvb2104-2-e}
create_clock -period 10 -name default
csim_design
csynth_design
