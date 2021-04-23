`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/11/27 11:51:25
// Design Name: 
// Module Name: ALU_led
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module ALU_led(
input clkin,
input[2:0] select,
output[7:0] scan,
output[7:0] seg7
    );
    
    wire[31:0] data_temp;
    wire clkout;
    
    ALU u0(
        .select(select),
        .y(data_temp)
        );
    
    led_seg7 u1(
        .clkin(clkin),
        .datain(data_temp),
        .scan(scan),
        .seg7(seg7)
    );
endmodule
