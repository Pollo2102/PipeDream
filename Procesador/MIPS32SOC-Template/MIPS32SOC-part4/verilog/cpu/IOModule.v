module IOModule(
    input [31:0] keypadIn,
    input addr,
    input en,
    output [31:0] keypadOut
);

reg [31:0]keypad[0:1];

assign keypad[addr] = en ? keypadIn : 32'b0;
assign keypadOut = keypad[addr];

endmodule