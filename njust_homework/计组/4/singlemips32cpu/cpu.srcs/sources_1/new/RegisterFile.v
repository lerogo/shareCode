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
     input CLK,                 // 时钟
     input RegWre,              // 写使能信号，为1时，在时钟上升沿写入
    input [4:0] rs,            // rs寄存器地址输入端口
    input [4:0] rt,            // rt寄存器地址输入端口
    input [4:0] WriteReg,      // 将数据写入的寄存器端口，其地址来源rt或rd字段
    input [31:0] WriteData,    // 写入寄存器的数据输入端口
     output [31:0] ReadData1,   // rs寄存器数据输出端口
    output [31:0] ReadData2    // rt寄存器数据输出端口
    );


    reg [31:0] register[0:15];  // 新建16个寄存器，用于操作
    // 初始时，将32个寄存器全部赋值为0
    integer i;
    initial 
     begin
        for(i = 0; i < 16; i = i + 1)  register[i] <= 0;
     end

    // 读寄存器
    assign ReadData1 = register[rs];
    assign ReadData2 = register[rt];

    // 写寄存器
    always@(negedge CLK)
     begin
        // 如果寄存器不为0，并且RegWre为真，写入数据
        if (RegWre && WriteReg != 0)  register[WriteReg] = WriteData;
     end 

endmodule