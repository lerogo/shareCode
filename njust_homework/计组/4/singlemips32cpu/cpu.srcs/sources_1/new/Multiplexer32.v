module Multiplexer32(
     input control,
    input [31:0] in1,
    input [31:0] in0,
    output [31:0] out
    );

    // 32线多路选择器
    assign out = control ? in1 : in0;

endmodule