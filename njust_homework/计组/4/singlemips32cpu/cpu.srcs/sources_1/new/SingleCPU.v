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

    // 各种临时变量
    wire [2:0] ALUOp; 
   wire [31:0] B, newAddress;
   wire [31:0] currentAddress_4, extendImmediate, currentAddress_immediate;   
   wire [4:0] WriteReg;  
   wire zero, PCSrc, PCWre, ALUSrcB, ALUM2Reg, RegWre, InsMemRW, DataMemRW, ExtSel, RegOut;


    /*module ControlUnit(
    input [5:0] op,         // op操作符
    input zero,             // ALU的zero输出
     // 一堆控制信号
     output PCSrc,           // 多路选择器
    output PCWre,           // (PC)PC是否更改，如果为0，PC不更改
    output ALUSrcB,         // 多路选择器
    output ALUM2Reg,        // 多路选择器
    output RegWre,          // (RF)写使能信号，为1时，在时钟上升沿写入
    output InsMemRW,        // (IM)读写控制信号，1为写，0位读
    output DataMemRW,       // (DM)数据存储器读写控制信号，为1写，为0读
    output ExtSel,          // (EXT)控制补位，如果为1，进行符号扩展，如果为0，全补0
    output RegOut,          // 多路选择器
    output [2:0] ALUOp      // (ALU)ALU操作控制 
    );*/
    ControlUnit cu(op, zero, PCSrc, PCWre, ALUSrcB, ALUM2Reg, RegWre, InsMemRW, DataMemRW, ExtSel, RegOut, ALUOp);

    /*module PC(
    input CLK,                         // 时钟
    input Reset,                       // 重置信号
    input PCWre,                       // PC是否更改，如果为0，PC不更改
    input [31:0] newAddress,           // 新指令
    output reg[31:0] currentAddress    // 当前指令
    );*/
    PC pc(CLK, Reset, PCWre, newAddress, currentAddress);

    /*module InstructionMemory(
     input InsMemRW,            // 读写控制信号，1为写，0位读
    input [31:0] IAddr,        // 指令地址输入入口
     //input IDataIn,             // 没用到 
    output [5:0] op,
    output [4:0] rs,
    output [4:0] rt,
    output [4:0] rd,
    output [15:0] immediate    // 指令代码分时段输出
    );*/
    InstructionMemory im(InsMemRW, currentAddress, op, rs, rt, rd, immediate);

    /*module RegisterFile(
     input CLK,                 // 时钟
     input RegWre,              // 写使能信号，为1时，在时钟上升沿写入
    input [4:0] rs,            // rs寄存器地址输入端口
    input [4:0] rt,            // rt寄存器地址输入端口
    input [4:0] WriteReg,      // 将数据写入的寄存器端口，其地址来源rt或rd字段
    input [31:0] WriteData,    // 写入寄存器的数据输入端口
    output [31:0] ReadData1,   // rs寄存器数据输出端口
    output [31:0] ReadData2    // rt寄存器数据输出端口
    );*/
    RegisterFile rf(CLK, RegWre, rs, rt, WriteReg, WriteData, ReadData1, ReadData2);

    /*module ALU(
     input [2:0] ALUOp,       // ALU操作控制
    input [31:0] A,          // 输入1
    input [31:0] B,          // 输入2
    output reg zero,             // 运算结果result的标志，result为0输出1，否则输出0
    output reg [31:0] result     // ALU运算结果
    );*/
    ALU alu(ALUOp, ReadData1, B, zero, result);

    /*module SignZeroExtend(
    input ExtSel,                  // 控制补位，如果为1，进行符号扩展，如果为0，全补0
    input [15:0] immediate,        // 16位立即数
    input [31:0] extendImmediate   // 输出的32位立即数
    );*/
    SignZeroExtend sze(ExtSel, immediate, extendImmediate);

    /*module DataMemory(
     input DataMemRW,            // 数据存储器读写控制信号，为1写，为0读
    input [31:0] DAddr,         // 数据存储器地址输入端口
    input [31:0] DataIn,        // 数据存储器数据输入端口
    output reg [31:0] DataOut   // 数据存储器数据输出端口
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