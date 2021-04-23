module Multiplexer5(
     input control,
    input [4:0] in1,
    input [4:0] in0,
    output [4:0] out
    );

    // 5线多路选择器
    assign out = control ? in1 : in0;

endmodule
