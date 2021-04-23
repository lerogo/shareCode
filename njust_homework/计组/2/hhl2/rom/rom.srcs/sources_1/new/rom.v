`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/01 16:12:07
// Design Name: 
// Module Name: rom
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

module rom(
input clkin,reset,wr,
input[15:0]addr,
output [31:0] dataout
    );
    reg[31:0] mem[0:65535];
    reg[31:0] dataout=32'd0;
     initial begin
     
     mem[0] =32'h00000001;
     mem[1] =32'h01010101;
     mem[5] =32'h03030303;
     mem[16] =32'h05050505;
     mem[28] =32'h25252525;
     mem[64] =32'h5a5a5a5a;
     mem[100] =32'h3b3b3b3b;
     mem[2000] =32'h4c4c4c4c;
     mem[30000] =32'h7d7d7d7d;
     mem[60000] =32'h1f1f1f1f;
     end
     
     
     always@(posedge clkin)
     begin 
     if(~wr) dataout = mem[addr];
     end
     
endmodule
