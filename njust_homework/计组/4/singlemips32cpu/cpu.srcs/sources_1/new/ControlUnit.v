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
    input [5:0] op,         // op操作符
    input zero,             // ALU的zero输出

     // 一堆控制信号
     output reg PCSrc,           // 多路选择器
    output reg PCWre,           // (PC)PC是否更改，如果为0，PC不更改
    output reg ALUSrcB,         // 多路选择器
    output reg ALUM2Reg,        // 多路选择器
    output reg RegWre,          // (RF)写使能信号，为1时，在时钟上升沿写入
    output reg InsMemRW,        // (IM)读写控制信号，1为写，0位读
    output reg DataMemRW,       // (DM)数据存储器读写控制信号，为1写，为0读
    output reg ExtSel,          // (EXT)控制补位，如果为1，进行符号扩展，如果为0，全补0
    output reg RegOut,          // 多路选择器
    output reg [2:0] ALUOp      // (ALU)ALU操作控制 
    );

    // 进行各种赋值
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
          begin   //以下都是控制单元产生的控制信号
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
          begin   //以下都是控制单元产生的控制信号
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
          begin   //以下都是控制单元产生的控制信号
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
             begin   //以下都是控制单元产生的控制信号
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
          begin   //以下都是控制单元产生的控制信号
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
          begin   //以下都是控制单元产生的控制信号
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
          begin   //以下都是控制单元产生的控制信号
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
          begin   //以下都是控制单元产生的控制信号
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
          begin   //以下都是控制单元产生的控制信号
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
          begin   //以下都是控制单元产生的控制信号
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
             begin   //以下都是控制单元产生的控制信号
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