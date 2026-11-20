# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\ajmix\Documents\ECE_520\Projects\mult_soc_dk\mult_soc_vitis\fifo_platform\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\ajmix\Documents\ECE_520\Projects\mult_soc_dk\mult_soc_vitis\fifo_platform\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {fifo_platform}\
-hw {C:\Users\ajmix\Documents\ECE_520\Projects\lab3_BRAM_FIFO\multiplier_example\proj\sc_fifo_system.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {C:/Users/ajmix/Documents/ECE_520/Projects/mult_soc_dk/mult_soc_vitis}

platform write
platform generate -domains 
platform active {fifo_platform}
domain active {zynq_fsbl}
bsp reload
bsp reload
bsp setdriver -ip sc_fifo_axi_0 -driver none -ver {}
bsp write
bsp reload
catch {bsp regenerate}
domain active {standalone_domain}
bsp reload
bsp setdriver -ip sc_fifo_axi_0 -driver none -ver {}
bsp write
bsp reload
catch {bsp regenerate}
platform generate
platform generate
