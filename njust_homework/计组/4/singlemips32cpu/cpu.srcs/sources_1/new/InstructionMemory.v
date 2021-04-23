`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:10:27 05/03/2017 
// Design Name: 
// Module Name:    IM 
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
module InstructionMemory(
     input InsMemRW,            // ��д�����źţ�1Ϊд��0λ��
    input [31:0] IAddr,        // ָ���ַ�������
     //input IDataIn,             // û�õ� 

    output [5:0] op,
    output [4:0] rs,
    output [4:0] rt,
    output [4:0] rd,
    output [15:0] immediate    // ָ������ʱ�����
    );

    reg[7:0] mem[0:63];  // �½�һ��32λ���������ڴ���ָ��

    initial 
     begin
        $readmemb("C:/Users/lerogo/Desktop/test.txt", mem);  //��ȡ�����ĵ��е�ָ��
     end

    // �ӵ�ַȡֵ��Ȼ�����
    assign op = mem[IAddr][7:2];
    assign rs[4:3] = mem[IAddr][1:0];
    assign rs[2:0] = mem[IAddr + 1][7:5];
    assign rt = mem[IAddr + 1][4:0];
    assign rd = mem[IAddr + 2][7:3];
    assign immediate[15:8] = mem[IAddr + 2];
    assign immediate[7:0] = mem[IAddr + 3];

endmodule