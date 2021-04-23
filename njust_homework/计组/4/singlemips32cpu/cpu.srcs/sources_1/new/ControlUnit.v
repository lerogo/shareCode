`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    02:11:08 05/03/2017 
// Design Name: 
// Module Name:    CU 
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
module ControlUnit(
    input [5:0] op,         // op������
    input zero,             // ALU��zero���

     // һ�ѿ����ź�
     output reg PCSrc,           // ��·ѡ����
    output reg PCWre,           // (PC)PC�Ƿ���ģ����Ϊ0��PC������
    output reg ALUSrcB,         // ��·ѡ����
    output reg ALUM2Reg,        // ��·ѡ����
    output reg RegWre,          // (RF)дʹ���źţ�Ϊ1ʱ����ʱ��������д��
    output reg InsMemRW,        // (IM)��д�����źţ�1Ϊд��0λ��
    output reg DataMemRW,       // (DM)���ݴ洢����д�����źţ�Ϊ1д��Ϊ0��
    output reg ExtSel,          // (EXT)���Ʋ�λ�����Ϊ1�����з�����չ�����Ϊ0��ȫ��0
    output reg RegOut,          // ��·ѡ����
    output reg [2:0] ALUOp      // (ALU)ALU�������� 
    );

    // ���и��ָ�ֵ
    initial 
     begin
        ExtSel = 0;
        PCWre = 1;
        InsMemRW = 1;
        RegOut = 1;
        RegWre = 0;
        ALUOp = 0;
        PCSrc = 0;
        ALUSrcB = 0;
        DataMemRW = 0;
        ALUM2Reg = 0;
    end

    always@(op or zero)
    begin  
      case(op) 
            // add
            6'b000000:
          begin   //���¶��ǿ��Ƶ�Ԫ�����Ŀ����ź�
                PCWre = 1;
                ALUSrcB = 0;
                ALUM2Reg = 0;
                RegWre = 1;
                InsMemRW = 1;
                DataMemRW = 0;
                ExtSel = 0;
                PCSrc = 0;
                RegOut = 1;
                ALUOp = 000;
             end
            // addi
            6'b000001:
          begin   //���¶��ǿ��Ƶ�Ԫ�����Ŀ����ź�
                PCWre = 1;
                ALUSrcB = 1;
                ALUM2Reg = 0;
                RegWre = 1;
                InsMemRW = 1;
                DataMemRW = 0;
                ExtSel = 1;
                PCSrc = 0;
                RegOut = 0;
                ALUOp = 000;
             end
            // sub
            6'b000010:
          begin   //���¶��ǿ��Ƶ�Ԫ�����Ŀ����ź�
                PCWre = 1;
                ALUSrcB = 0;
                ALUM2Reg = 0;
                RegWre = 1;
                InsMemRW = 1;
                DataMemRW = 0;
                ExtSel = 0;
                PCSrc = 0;
                RegOut = 1;
                ALUOp = 001;
             end
            // ori
            6'b010000:
             begin   //���¶��ǿ��Ƶ�Ԫ�����Ŀ����ź�
                PCWre = 1;
                ALUSrcB = 1;
                ALUM2Reg = 0;
                RegWre = 1;
                InsMemRW = 1;
                DataMemRW = 0;
                ExtSel = 0;
                PCSrc = 0;
                RegOut = 0;
                ALUOp = 011;
          end
           // and
         6'b010001:
          begin   //���¶��ǿ��Ƶ�Ԫ�����Ŀ����ź�
                PCWre = 1;
                ALUSrcB = 0;
                ALUM2Reg = 0;
                RegWre = 1;
                InsMemRW = 1;
                DataMemRW = 0;
                ExtSel = 0;
                PCSrc = 0;
                RegOut = 1;
                ALUOp = 100;
          end
            // or
            6'b010010:
          begin   //���¶��ǿ��Ƶ�Ԫ�����Ŀ����ź�
                PCWre = 1;
                ALUSrcB = 0;
                ALUM2Reg = 0;
                RegWre = 1;
                InsMemRW = 1;
                DataMemRW = 0;
                ExtSel = 0;
                PCSrc = 0;
                RegOut = 1;
                ALUOp = 011;
             end
           // move
         6'b100000:
          begin   //���¶��ǿ��Ƶ�Ԫ�����Ŀ����ź�
                PCWre = 1;
                ALUSrcB = 0;
                ALUM2Reg = 0;
                RegWre = 1;
                InsMemRW = 1;
                DataMemRW = 0;
                ExtSel = 0;
                PCSrc = 0;
                RegOut = 1;
                ALUOp = 000;
          end
            // sw
            6'b100110:
          begin   //���¶��ǿ��Ƶ�Ԫ�����Ŀ����ź�
                PCWre = 1;
                ALUSrcB = 1;
                ALUM2Reg = 0;
                RegWre = 0;
                InsMemRW = 1;
                DataMemRW = 1;
                ExtSel = 1;
                PCSrc = 0;
                RegOut = 0;
                ALUOp = 000;
          end
         // lw
            6'b100111:
          begin   //���¶��ǿ��Ƶ�Ԫ�����Ŀ����ź�
                PCWre = 1;
                ALUSrcB = 1;
                ALUM2Reg = 1;
                RegWre = 1;
                InsMemRW = 1;
                DataMemRW = 0;
                ExtSel = 1;
                PCSrc = 0;
                RegOut = 0;
                ALUOp = 000;
          end
         // beq
           6'b110000:
          begin   //���¶��ǿ��Ƶ�Ԫ�����Ŀ����ź�
                if (zero) begin
                    PCSrc = 1;
                end else begin
                    PCSrc = 0;
                end
            ALUM2Reg = 0;
                PCWre = 1;
                ALUSrcB = 0;
                RegWre = 0;
                InsMemRW = 1;
                DataMemRW = 0;
                ExtSel = 1;
                RegOut = 0;
                ALUOp = 001;
          end
           // halt
           6'b111111:
             begin   //���¶��ǿ��Ƶ�Ԫ�����Ŀ����ź�
                PCWre = 0;
                ALUSrcB = 0;
                ALUM2Reg = 0;
                RegWre = 0;
                InsMemRW = 0;
                DataMemRW = 0;
                ExtSel = 0;
                PCSrc = 0;
                RegOut = 0;
                ALUOp = 000;
             end
        endcase
     end

endmodule