`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    01:37:40 05/03/2017 
// Design Name: 
// Module Name:    DM 
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
module DataMemory(
    input CLK, 
    input DataMemRW,            // ���ݴ洢����д�����źţ�Ϊ1д��Ϊ0��
    input [31:0] DAddr,         // ���ݴ洢����ַ����˿�
    input [31:0] DataIn,        // ���ݴ洢����������˿�
    output [31:0] DataOut   // ���ݴ洢����������˿�
    );

    // ģ���ڴ棬��8λΪһ�ֽڴ洢����64�ֽ�
    reg [7:0] memory[0:63];
    reg [31:0] DataOut;
    // ��ʼ��ֵ
    integer i;
    initial
     begin
        for (i = 0; i < 64; i = i + 1)  memory[i] <= 0;
     end

    // ��д�ڴ�
   // always@(posedge clk)
    // begin

     //end

    always@(posedge CLK)
     begin
        // д�ڴ�
        if (DataMemRW)
         begin
           memory[DAddr] <= DataIn[31:24];
            memory[DAddr + 1] <= DataIn[23:16];
            memory[DAddr + 2] <= DataIn[15:8];
            memory[DAddr + 3] <= DataIn[7:0];
         end
        // ���ڴ�
        else
         begin
            DataOut[31:24] <= memory[DAddr];
            DataOut[23:16] <= memory[DAddr + 1];
            DataOut[15:8] <= memory[DAddr + 2];
            DataOut[7:0] <= memory[DAddr + 3];
         end
     end

endmodule