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
     input [2:0] ALUOp,           // ALU��������
    input [31:0] A,              // ����1
    input [31:0] B,              // ����2
    output reg zero,             // ������result�ı�־��resultΪ0���1���������0
    output reg [31:0] result     // ALU������
    );

    // ����ALU����
    always@(*)
     begin
        // ��������
        case (ALUOp)
            3'b000 : result = A + B;  // �ӷ�
            3'b001 : result = A - B;  // ����
            3'b010 : result = B - A;  // ����
            3'b011 : result = A | B;  // ��
            3'b100 : result = A & B;  // ��
            3'b101 : result = ~A & B;  // A����B
            3'b110 : result = A ^ B;  // ���
            3'b111 : result = ~A ^ B;  // ͬ��
            default : result = 0;
        endcase
        // ����zero
        if (result)  zero = 0;
        else  zero = 1;
     end

endmodule