open_project dot_product_prj
set_top kernel_top
add_files kernel_top.cpp
add_files -tb main.cpp

open_solution "solution0"
set_part {xcku115-flvb2104-2-e}
create_clock -period 10 -name default
config_compile -unsafe_math_optimizations
csim_design
csynth_design
cosim_design -rtl verilog -trace_level all

#export_design -evaluate verilog -format ipxact
