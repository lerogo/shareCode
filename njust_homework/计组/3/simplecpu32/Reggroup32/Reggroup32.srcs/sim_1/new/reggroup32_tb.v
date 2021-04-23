`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/08 15:51:38
// Design Name: 
// Module Name: reggroup32_tb
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


module reggroup32_tb(
        
    );
    reg clkin, regwr;
    reg [4:0] waddr;
    reg [4:0] raddr1;
    reg [4:0] raddr2;
    reg [31:0] datain;
    wire [31:0] dataout1;
    wire [31:0] dataout2;
    
    reggroup32 u0(.clkin(clkin), .regwr(regwr), .waddr(waddr), .raddr1(raddr1), .raddr2(raddr2),.datain(datain), .dataout1(dataout1),.dataout2(dataout2) );
    
    initial begin
        clkin = 0; #20;
    end
    
    always #10 clkin = ~clkin;
    
    always begin
        regwr = 0; #20;
        regwr = 1; #220;
    end
    
    always begin
        datain = 32'h00000001; #40;
        datain = 32'h00000010; #40;
        datain = 32'h00000100; #40;
        datain = 32'h00001000; #40;
        datain = 32'h00010000; #40;
        datain = 32'h10000000; #40;
    end
    
    always begin
        waddr = 5'd0 ; #40;
        waddr = 5'd4 ; #40;
        waddr = 5'd8 ; #40;
        waddr = 5'd16 ; #40;
        waddr = 5'd25 ; #40;
        waddr = 5'd30 ; #40;
    end
    
    always begin
        raddr1 = 5'd0 ; #40;
        raddr1 = 5'd4 ; #40;
        raddr1 = 5'd8 ; #40;
        raddr1 = 5'd16 ; #40;
        raddr1 = 5'd25 ; #40;
        raddr1 = 5'd30 ; #40;
        raddr1 = 5'd31 ; #40;
        end
        
    always begin
        raddr2 = 5'd0 ; #40;
        raddr2 = 5'd4 ; #40;
        raddr2 = 5'd8 ; #40;
        raddr2 = 5'd16 ; #40;
        raddr2 = 5'd25 ; #40;
        raddr2 = 5'd30 ; #40;
        raddr2 = 5'd2 ; #40;
    end
            
endmodule
