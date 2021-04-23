`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    01:07:13 05/03/2017 
// Design Name: 
// Module Name:    RF 
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
module RegisterFile(
     input CLK,                 // ʱ��
     input RegWre,              // дʹ���źţ�Ϊ1ʱ����ʱ��������д��
    input [4:0] rs,            // rs�Ĵ�����ַ����˿�
    input [4:0] rt,            // rt�Ĵ�����ַ����˿�
    input [4:0] WriteReg,      // ������д��ļĴ����˿ڣ����ַ��Դrt��rd�ֶ�
    input [31:0] WriteData,    // д��Ĵ�������������˿�
     output [31:0] ReadData1,   // rs�Ĵ�����������˿�
    output [31:0] ReadData2    // rt�Ĵ�����������˿�
    );


    reg [31:0] register[0:15];  // �½�16���Ĵ��������ڲ���
    // ��ʼʱ����32���Ĵ���ȫ����ֵΪ0
    integer i;
    initial 
     begin
        for(i = 0; i < 16; i = i + 1)  register[i] <= 0;
     end

    // ���Ĵ���
    assign ReadData1 = register[rs];
    assign ReadData2 = register[rt];

    // д�Ĵ���
    always@(negedge CLK)
     begin
        // ����Ĵ�����Ϊ0������RegWreΪ�棬д������
        if (RegWre && WriteReg != 0)  register[WriteReg] = WriteData;
     end 

endmodule