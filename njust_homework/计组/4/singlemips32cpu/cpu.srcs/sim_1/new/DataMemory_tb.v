`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/11/14 14:36:43
// Design Name: 
// Module Name: DataMemory_tb
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

module DataMemory_tb(

    );
   reg CLK;
   reg DataMemRW;
   reg [31:0] DAddr;
   reg [31:0] DataIn;
   wire [31:0] DataOut;
   
   DataMemory u0(.CLK(CLK),.DataMemRW(DataMemRW),.DAddr(DAddr),.DataIn(DataIn),.DataOut(DataOut));
   
   initial begin
    #10; CLK =0; 
    #10; DataMemRW = 0 ;
    #10; DAddr = 32'h00000000;
    #10; DataIn = 32'h0000000;
  end
  
   always #5 CLK = ~CLK;
   
   always begin
   DataMemRW = 1 ; #160;
   DataMemRW = 0 ; #160;
   end
   
   always begin
   DAddr = 32'h00000000; #20;
   DAddr = 32'h00000004; #20;
   DAddr = 32'h00000008; #20;
   DAddr = 32'h0000000c; #20;  
   DAddr = 32'h000000010; #20;
   DAddr = 32'h000000020; #20;
   DAddr = 32'h00000024; #20;
   DAddr = 32'h00000028; #20;
   
   end
   
   always begin
    DataIn = 32'h01010101;#20;
    DataIn = 32'h02020202;#20;
    DataIn = 32'h05050505;#20;
    DataIn = 32'h07070707;#20;
    DataIn = 32'h0a0a0a0a;#20;
    DataIn = 32'h00ff00ff;#20;
    DataIn = 32'h10101010;#20;
    DataIn = 32'h20202020;#20;
  end      
endmodule
