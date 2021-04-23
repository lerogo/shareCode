`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/01 16:13:08
// Design Name: 
// Module Name: rom_tb
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



module rom_tb(

    );
    reg clkin, wr;
    reg[15:0] addr;
    wire[31:0] dataout;
    rom v0(.clkin(clkin), .wr(wr), .addr(addr), .dataout(dataout));
    initial begin
    clkin=0;#20;
    wr=0;#20;
    end
 always #10 clkin=~clkin;
    
    always begin
    wr=0;#160;
    wr= 1;#160;
    end
    always begin
    addr=16'd0;#20;
    addr=16'd1;#20;
    addr=16'd5;#20;
    addr=16'd16;#20;
    addr=16'd28;#20;
    addr=16'd64;#20;
    addr=16'd100;#20;
    addr=16'd2000;#20;
    addr=16'd30000;#20;
    addr=16'd60000;#20;
   end
   
endmodule