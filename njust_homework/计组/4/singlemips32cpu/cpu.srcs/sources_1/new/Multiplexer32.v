module Multiplexer32(
     input control,
    input [31:0] in1,
    input [31:0] in0,
    output [31:0] out
    );

    // 32�߶�·ѡ����
    assign out = control ? in1 : in0;

endmodule