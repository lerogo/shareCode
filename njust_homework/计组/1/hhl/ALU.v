`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/11/27 11:37:27
// Design Name: 
// Module Name: ALU
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


module ALU(
input[2:0] select,
output[31:0] y
    );
    reg[31:0] x1 = 6, x2 = 3;
    wire[2:0] select;
    reg[31:0] y;
    reg[31:0] temp;
    
    always@(select or x1 or x2)
    begin
        case(select)
            3'b000: y = x1 & x2;
            3'b001: y = x1 | x2;
            3'b010: y = x1 << x2;
            3'b011: y = x1 + x2;
            3'b100: y = x1 - x2;
            3'b101: y = x1 * x2;
            default: y = 0;
         endcase
      end                
endmodule
