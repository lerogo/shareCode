`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    01:54:18 05/03/2017 
// Design Name: 
// Module Name:    ALU 
// Project Name: 
// Target Devices: 
// Tool versions: 
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
     input [2:0] ALUOp,           // ALU操作控制
    input [31:0] A,              // 输入1
    input [31:0] B,              // 输入2
    output reg zero,             // 运算结果result的标志，result为0输出1，否则输出0
    output reg [31:0] result     // ALU运算结果
    );

    // 进行ALU计算
    always@(*)
     begin
        // 进行运算
        case (ALUOp)
            3'b000 : result = A + B;  // 加法
            3'b001 : result = A - B;  // 减法
            3'b010 : result = B - A;  // 减法
            3'b011 : result = A | B;  // 或
            3'b100 : result = A & B;  // 与
            3'b101 : result = ~A & B;  // A非与B
            3'b110 : result = A ^ B;  // 异或
            3'b111 : result = ~A ^ B;  // 同或
            default : result = 0;
        endcase
        // 设置zero
        if (result)  zero = 0;
        else  zero = 1;
     end

endmodule