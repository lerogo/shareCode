`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:58:20 05/03/2017 
// Design Name: 
// Module Name:    EX 
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
module SignZeroExtend(
    input ExtSel,                  // ���Ʋ�λ�����Ϊ1�����з�����չ�����Ϊ0��ȫ��0
    input [15:0] immediate,        // 16λ������
    output [31:0] extendImmediate   // �����32λ������
    );

    // ������չ
    assign extendImmediate[15:0] = immediate;
    assign extendImmediate[31:16] = ExtSel ? (immediate[15] ? 16'hffff : 16'h0000) : 16'h0000;

endmodule