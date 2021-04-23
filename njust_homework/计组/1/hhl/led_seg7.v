`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/11/15 10:06:37
// Design Name: 
// Module Name: seg7
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


module led_seg7(
input clkin,
input [31:0] datain,
output [7:0] scan,
output [7:0] seg7
    );
    
 reg [7:0] scan;
 reg [7:0] seg7=0;
 reg [2:0] cnt1=0;
 reg [3:0] data_temp;
 reg clkout=0;
 
 reg[31:0] cnt=0;
 reg clk_temp=0;
 
 //50MHZ,20ns,500000*20ns=100ms
 always @(posedge clkin) begin
     case(cnt)
         32'd50000: begin            
             clk_temp <= ~clk_temp;
             cnt <= 0;
             end             
         default: begin
             cnt <= cnt + 1;
             end
     endcase
     clkout <= clk_temp;
 end
    
 always @(posedge clkout)
   begin
       // if(~reset) 
      //      begin
      //          cnt1 = 3'b000;
      //         scan = 8'b11111111;              
     //       end
       
             if(cnt1 == 3'b111) 
                cnt1 = 3'b000;                
             else
                cnt1 = cnt1 + 1 ;     
            //end
   end
   
   always @(cnt1)
   begin     
       case(cnt1)
            3'b000 : begin scan <= 8'b11111110; data_temp <= datain[3:0];    end   
            3'b001 : begin scan <= 8'b11111101; data_temp <= datain[7:4];    end  
            3'b010 : begin scan <= 8'b11111011; data_temp <= datain[11:8];   end      
            3'b011 : begin scan <= 8'b11110111; data_temp <= datain[15:12];  end
            3'b100 : begin scan <= 8'b11101111; data_temp <= datain[19:16];  end      
            3'b101 : begin scan <= 8'b11011111; data_temp <= datain[23:20];  end   
            3'b110 : begin scan <= 8'b10111111; data_temp <= datain[27:24];  end      
            3'b111 : begin scan <= 8'b01111111; data_temp <= datain[31:28];  end   
            default: begin scan <= 8'b11111111; data_temp <= 32'd0;  end
        endcase    
       
        case(data_temp)
                  4'b0000 : seg7 <= 8'b00111111;    
                  4'b0001 : seg7 <= 8'b00000110;  
                  4'b0010 : seg7 <= 8'b01011011;        
                  4'b0011 : seg7 <= 8'b01001111;
                  4'b0100 : seg7 <= 8'b01100110;
                  4'b0101 : seg7 <= 8'b01101101;
                  4'b0110 : seg7 <= 8'b01111101;
                  4'b0111 : seg7 <= 8'b00000111;
                  4'b1000 : seg7 <= 8'b01111111;
                  4'b1001 : seg7 <= 8'b01101111;
                  4'b1010 : seg7 <= 8'b01110111;
                  4'b1011 : seg7 <= 8'b01111100;
                  4'b1100 : seg7 <= 8'b00111001;
                  4'b1101 : seg7 <= 8'b01011110;   
                  4'b1110 : seg7 <= 8'b01111001;
                  4'b1111 : seg7 <= 8'b01110001;                                         
                  default : seg7 <= 8'b00000000;
        endcase
 end
endmodule