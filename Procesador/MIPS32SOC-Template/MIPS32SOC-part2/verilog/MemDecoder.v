module MemDecoder (
    input [31:0] virtualAddr,
    input usingMemDecoder,
    input memWrite,
    output [10:0] physicalAddr,
    output memEn,
    output invAddr
);

// Global = 0x10010000 - 0x10011000
// Stack = 0x7FFFEFFC - 0x7FFFFFFC

//reg [31:0] physicalAddrWire;
//assign physicalAddr = physicalAddrWire[12:2];

wire [10:0] globalAddress;
assign globalAddress = virtualAddr[12:2]; 

wire [10:0] stackAddress;
assign stackAddress = virtualAddr[12:2] + 11'h400;

always @(*)
begin
    if (!usingMemDecoder)
    begin
        invAddr = 0;
        physicalAddr = 0;
        memEn = 0;
    end
    else
    begin
        if ((virtualAddr < 32'h10010000) || (virtualAddr >= 32'h10011000 && virtualAddr <                32'h7FFFEFFC) || (virtualAddr >= 32'h7FFFFFFC))
            begin
                invAddr = 1'd1;
                physicalAddr = 11'h0;
                memEn = 0;
            end
        else
            begin
                if (virtualAddr >= 32'h7FFFEFFC && virtualAddr < 32'h7FFFFFFC)
                begin
                    invAddr = 1'd0;
                    //physicalAddrWire = virtualAddr - 32'h7FFFEFFC;
                    physicalAddr = stackAddress;
                    memEn = memWrite;
                end
                else if (virtualAddr >= 32'h10010000 && virtualAddr < 32'h10011000)
                begin
                    invAddr = 1'd0;
                    //physicalAddrWire = virtualAddr + 32'h1400;
                    physicalAddr = globalAddress;
                    memEn = memWrite;
                end
            end
    end
    
end
endmodule