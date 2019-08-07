module BitExtender (
    input extend, //! If x==0, do sign extend, else do zero extend
    input [15:0] in, //! Input value (16 bits)
    output [31:0] out //! Extended output value (32 bits)
);

    always @ (extend or in) begin
        if (~extend)
            out = {{16{in[15]}}, in};
        else
            out = {16'h0, in};
    end
endmodule

