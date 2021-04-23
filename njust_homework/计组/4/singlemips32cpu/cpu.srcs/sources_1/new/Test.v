`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/04/24 01:21:55
// Design Name: 
// Module Name: cpu_sim
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   23:01:04 05/02/2017
// Design Name:   MainSource
// Module Name:   D:/Single/SingleCPU/Text.v
// Project Name:  SingleCPU
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: MainSource
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module Text;

	// Inputs
	reg [7:0] x_in;
	reg flag;

	// Outputs
	wire [7:0] y_out;

	// Instantiate the Unit Under Test (UUT)
	MainSource uut (
		.x_in(x_in), 
		.flag(flag), 
		.y_out(y_out)
	);

	initial begin
		// Initialize Inputs
		x_in = 0;
		flag = 0;

		// Wait 100 ns for global reset to finish
// Wait 100 ns for global reset to finish
#100; //100ns
x_in = 8'h21;
flag = 0;
// Add stimulus here
#100; //200ns
x_in = 8'h01;
flag = 1;
#100; //300ns
x_in = 8'h0f;
flag = 0;
#100; //400ns
x_in = 8'hf0;
flag = 1;
#100 $stop; //500ns


	end
      
endmodule


