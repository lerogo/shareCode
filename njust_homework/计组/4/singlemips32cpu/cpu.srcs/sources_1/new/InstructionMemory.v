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
     input InsMemRW,            // 读写控制信号，1为写，0位读
    input [31:0] IAddr,        // 指令地址输入入口
     //input IDataIn,             // 没用到 

    output [5:0] op,
    output [4:0] rs,
    output [4:0] rt,
    output [4:0] rd,
    output [15:0] immediate    // 指令代码分时段输出
    );

    reg[7:0] mem[0:63];  // 新建一个32位的数组用于储存指令

    initial 
     begin
        $readmemb("C:/Users/lerogo/Desktop/test.txt", mem);  //读取测试文档中的指令
     end

    // 从地址取值，然后输出
    assign op = mem[IAddr][7:2];
    assign rs[4:3] = mem[IAddr][1:0];
    assign rs[2:0] = mem[IAddr + 1][7:5];
    assign rt = mem[IAddr + 1][4:0];
    assign rd = mem[IAddr + 2][7:3];
    assign immediate[15:8] = mem[IAddr + 2];
    assign immediate[7:0] = mem[IAddr + 3];

endmodule