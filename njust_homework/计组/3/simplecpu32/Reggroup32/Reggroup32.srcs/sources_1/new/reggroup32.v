`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/08 15:41:18
// Design Name: 
// Module Name: reggroup32
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


module reggroup32(
    input clkin, regwr,
    input [4:0] waddr,
    input [4:0] raddr1,
    input [4:0] raddr2,
    input [31:0] datain,
    output [31:0] dataout1,
    output [31:0] dataout2
    );
    
    reg [31:0] mem[0:31];
    
    integer i = 0;
    initial begin
        for (i = 0 ; i < 32; i = i + 1)
            mem[i] <= 0;
    end
    
    always @ (posedge clkin) 
        begin
            if (regwr)
                mem[waddr] <= datain;
    end
    
    assign dataout1 = mem[raddr1];
    assign dataout2 = mem[raddr2];
    
endmodule
