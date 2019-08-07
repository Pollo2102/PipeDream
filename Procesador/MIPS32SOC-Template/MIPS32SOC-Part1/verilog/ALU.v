`include "alu_defines.vh"

module ALU(
    input [31:0] a,
    input [31:0] b,
    input [2:0] func,
    output reg [31:0] res,
    output isZero
    );

    assign isZero = (res == 32'd0);

    always @ (func or a or b)
    begin
        case (func)
            `ALU_ADD: res = a + b; 
            `ALU_SUB: res = a - b;
            `ALU_AND: res = a & b;
            `ALU_OR : res = a | b;
            `ALU_SLT: res = {31'd0, $signed(a) < $signed(b)};
            default:
                    res = 32'hX;
        endcase
    end

endmodule
