`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   08:41:45 05/03/2017
// Design Name:   SingleCPU
// Module Name:   D:/Single/SingleCPU/SingleCPUTest.v
// Project Name:  SingleCPU
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: SingleCPU
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////
 
module SingleCPUTest;

	// Inputs
	reg CLK;
	reg Reset;

	// Outputs
	wire [5:0] op;
	wire [4:0] rs;
	wire [4:0] rt;
	wire [4:0] rd;
	wire [15:0] immediate;
	wire [31:0] ReadData1;
	wire [31:0] ReadData2;
	wire [31:0] WriteData;
	wire [31:0] DataOut;
	wire [31:0] currentAddress;
	wire [31:0] result;

	// Instantiate the Unit Under Test (UUT)
	SingleCPU uut (
		.CLK(CLK), 
		.Reset(Reset), 
		.op(op), 
		.rs(rs),
		.rt(rt),
		.rd(rd),
		.immediate(immediate),
		.ReadData1(ReadData1), 
		.ReadData2(ReadData2),
		.WriteData(WriteData),
		.DataOut(DataOut),
		.currentAddress(currentAddress), 
		.result(result)
	);

	initial begin
		// Initialize Inputs
		CLK = 0;
		Reset = 1;

		// Wait 50 ns for global reset to finish
		#50; // �տ�ʼ����pcΪ0
         CLK = !CLK;  // �½��أ�ʹPC������
      #50;
         Reset = 0;  // ��������ź�
      forever #50
		 begin // ����ʱ���źţ�����Ϊ50s
         CLK = !CLK;
       end
       
		// Add stimulus here

	end
      
endmodule