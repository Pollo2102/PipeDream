module IOModule(
    input [31:0] keypadIn,
    input en,
    output [31:0] keypadOut
);

assign keypadOut = en ? keypadIn : 32'h0;

endmodule