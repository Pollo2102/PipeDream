module MemodyDecoder (
    input [31:0] virtualAddr,
    output [10:0] physicalAddr,
    output invAddr
);

// Global = 0x10010000 - 0x10011000
// Stack = 0x7FFFEFFC - 0x7FFFFFFC

wire [31:0] physicalAddrWire;
assign physicalAddr = physicalAddrWire[12:2];

always @(*)
begin
    if ((virtualAddr < 32'h10010000) || (virtualAddr > 32'h10011000 && virtualAddr <                32'h7FFFEFFC) || (virtualAddr > 32'h7FFFFFFC))
    begin
        invAddr = 1'd1;
        physicalAddr = 'hx;
    end
    else
    begin
        if (virtualAddr >= 32'h7FFFEFFC && virtualAddr <= 32'h7FFFFFFC)
        begin
            invAddr = 1'd0;
            physicalAddr = virtualAddr - 32'h7FFFEFFC;
        end
        else if (virtualAddr >= 32'h10010000 && virtualAddr <= 32'h10011000)
        begin
            invAddr = 1'd0;
            physicalAddr = virtualAddr + 32'h1400;
        end
    end
end
endmodule