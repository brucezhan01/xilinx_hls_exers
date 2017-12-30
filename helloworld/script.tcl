open_project hello_prj
set_top hello_core
add_files hello.cpp
add_files -tb test_hello.cpp

open_solution "solution0"
set_part {xcku115-flvf1924-3-e}
#set_part {xc7z020clg484-1}
create_clock -period 10 -name default
csim_design -clean
csynth_design
