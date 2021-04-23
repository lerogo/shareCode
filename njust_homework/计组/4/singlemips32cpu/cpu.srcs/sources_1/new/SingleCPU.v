`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:43:17 05/02/2017 
// Design Name: 
// Module Name:    SingleCPU 
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
module SingleCPU(
    input CLK,
    input Reset,
    output [5:0] op,
     output [4:0] rs,
     output [4:0] rt,
     output [4:0] rd,
     output [15:0] immediate,
    output [31:0] ReadData1,
    output [31:0] ReadData2,
     output [31:0] WriteData,
     output [31:0] DataOut,
    output [31:0] currentAddress,
    output [31:0] result
    );

    // ������ʱ����
    wire [2:0] ALUOp; 
   wire [31:0] B, newAddress;
   wire [31:0] currentAddress_4, extendImmediate, currentAddress_immediate;   
   wire [4:0] WriteReg;  
   wire zero, PCSrc, PCWre, ALUSrcB, ALUM2Reg, RegWre, InsMemRW, DataMemRW, ExtSel, RegOut;


    /*module ControlUnit(
    input [5:0] op,         // op������
    input zero,             // ALU��zero���
     // һ�ѿ����ź�
     output PCSrc,           // ��·ѡ����
    output PCWre,           // (PC)PC�Ƿ���ģ����Ϊ0��PC������
    output ALUSrcB,         // ��·ѡ����
    output ALUM2Reg,        // ��·ѡ����
    output RegWre,          // (RF)дʹ���źţ�Ϊ1ʱ����ʱ��������д��
    output InsMemRW,        // (IM)��д�����źţ�1Ϊд��0λ��
    output DataMemRW,       // (DM)���ݴ洢����д�����źţ�Ϊ1д��Ϊ0��
    output ExtSel,          // (EXT)���Ʋ�λ�����Ϊ1�����з�����չ�����Ϊ0��ȫ��0
    output RegOut,          // ��·ѡ����
    output [2:0] ALUOp      // (ALU)ALU�������� 
    );*/
    ControlUnit cu(op, zero, PCSrc, PCWre, ALUSrcB, ALUM2Reg, RegWre, InsMemRW, DataMemRW, ExtSel, RegOut, ALUOp);

    /*module PC(
    input CLK,                         // ʱ��
    input Reset,                       // �����ź�
    input PCWre,                       // PC�Ƿ���ģ����Ϊ0��PC������
    input [31:0] newAddress,           // ��ָ��
    output reg[31:0] currentAddress    // ��ǰָ��
    );*/
    PC pc(CLK, Reset, PCWre, newAddress, currentAddress);

    /*module InstructionMemory(
     input InsMemRW,            // ��д�����źţ�1Ϊд��0λ��
    input [31:0] IAddr,        // ָ���ַ�������
     //input IDataIn,             // û�õ� 
    output [5:0] op,
    output [4:0] rs,
    output [4:0] rt,
    output [4:0] rd,
    output [15:0] immediate    // ָ������ʱ�����
    );*/
    InstructionMemory im(InsMemRW, currentAddress, op, rs, rt, rd, immediate);

    /*module RegisterFile(
     input CLK,                 // ʱ��
     input RegWre,              // дʹ���źţ�Ϊ1ʱ����ʱ��������д��
    input [4:0] rs,            // rs�Ĵ�����ַ����˿�
    input [4:0] rt,            // rt�Ĵ�����ַ����˿�
    input [4:0] WriteReg,      // ������д��ļĴ����˿ڣ����ַ��Դrt��rd�ֶ�
    input [31:0] WriteData,    // д��Ĵ�������������˿�
    output [31:0] ReadData1,   // rs�Ĵ�����������˿�
    output [31:0] ReadData2    // rt�Ĵ�����������˿�
    );*/
    RegisterFile rf(CLK, RegWre, rs, rt, WriteReg, WriteData, ReadData1, ReadData2);

    /*module ALU(
     input [2:0] ALUOp,       // ALU��������
    input [31:0] A,          // ����1
    input [31:0] B,          // ����2
    output reg zero,             // ������result�ı�־��resultΪ0���1���������0
    output reg [31:0] result     // ALU������
    );*/
    ALU alu(ALUOp, ReadData1, B, zero, result);

    /*module SignZeroExtend(
    input ExtSel,                  // ���Ʋ�λ�����Ϊ1�����з�����չ�����Ϊ0��ȫ��0
    input [15:0] immediate,        // 16λ������
    input [31:0] extendImmediate   // �����32λ������
    );*/
    SignZeroExtend sze(ExtSel, immediate, extendImmediate);

    /*module DataMemory(
     input DataMemRW,            // ���ݴ洢����д�����źţ�Ϊ1д��Ϊ0��
    input [31:0] DAddr,         // ���ݴ洢����ַ����˿�
    input [31:0] DataIn,        // ���ݴ洢����������˿�
    output reg [31:0] DataOut   // ���ݴ洢����������˿�
    );*/
    DataMemory dm(CLK,DataMemRW, result, ReadData2, DataOut);

    assign currentAddress_4 = currentAddress + 4;
    assign currentAddress_immediate = currentAddress_4 + (extendImmediate << 2);
    //ADD add1(currentAddress, 32'h00000004, currentAddress_4);
    //ADD add1(currentAddress_4, extendImmediate << 2, currentAddress_immediate);

    Multiplexer5 m5(RegOut, rd, rt, WriteReg);

    Multiplexer32 m321(ALUSrcB, extendImmediate, ReadData2, B);
    Multiplexer32 m322(ALUM2Reg, DataOut, result, WriteData);
    Multiplexer32 m323(PCSrc, currentAddress_immediate, currentAddress_4, newAddress);

endmodule