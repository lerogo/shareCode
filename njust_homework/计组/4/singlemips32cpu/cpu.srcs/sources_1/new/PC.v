`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:43:40 05/02/2017 
// Design Name: 
// Module Name:    PC 
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
module PC(
    input CLK,                         // ʱ��
    input Reset,                       // �����ź�
    input PCWre,                       // PC�Ƿ���ģ����Ϊ0��PC������
    input [31:0] newAddress,           // ��ָ��
    output reg[31:0] currentAddress    // ��ǰָ��
    );

    initial begin
        currentAddress <= 0;  // ��������ֵ
    end

    always@(posedge CLK or posedge Reset)
     begin
        if (Reset == 1)  currentAddress <= 0;  // ������ã���ֵΪ0
        else 
         begin
            if (PCWre)  currentAddress <= newAddress;
            else  currentAddress <= currentAddress;
         end
     end

endmodule
