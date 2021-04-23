@echo off
set xv_path=C:\\Xilinx\\Vivado\\2017.1\\bin
call %xv_path%/xsim SingleCPU_tb_behav -key {Behavioral:sim_1:Functional:SingleCPU_tb} -tclbatch SingleCPU_tb.tcl -view E:/singleMIPSCPU32/cpu/SingleCPU_tb_behav.wcfg -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
