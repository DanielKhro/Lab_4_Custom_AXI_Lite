# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\ajmix\Documents\ECE_520\Projects\mult_soc_dk\mult_soc_vitis\mult_app_v2\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\ajmix\Documents\ECE_520\Projects\mult_soc_dk\mult_soc_vitis\mult_app_v2\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {mult_app_v2}\
-hw {C:\Users\ajmix\Documents\ECE_520\Projects\mult_soc_dk\mult_bd_dk_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {C:/Users/ajmix/Documents/ECE_520/Projects/mult_soc_dk/mult_soc_vitis}

platform write
platform generate -domains 
platform active {mult_app_v2}
domain active {zynq_fsbl}
bsp reload
bsp setdriver -ip mult_16_bit_0 -driver none -ver {}
bsp write
bsp reload
catch {bsp regenerate}
domain active {standalone_domain}
bsp reload
bsp setdriver -ip mult_16_bit_0 -driver none -ver {}
bsp write
bsp reload
catch {bsp regenerate}
bsp write
domain active {zynq_fsbl}
bsp write
platform generate
bsp write
domain active {standalone_domain}
bsp reload
platform generate -domains 
platform config -updatehw {C:/Users/ajmix/Documents/ECE_520/Projects/mult_soc_dk/mult_bd_dk_wrapper.xsa}
domain active {zynq_fsbl}
bsp reload
bsp write
domain active {standalone_domain}
bsp reload
bsp write
domain active {zynq_fsbl}
bsp write
platform generate -domains 
