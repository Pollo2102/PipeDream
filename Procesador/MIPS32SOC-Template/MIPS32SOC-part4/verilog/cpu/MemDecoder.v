module MemDecoder (
    input [31:0] virtualAddr,
    input memWrite,
    input memRead,
    output reg [10:0] physAddr,
    output reg [2:0] memEn,
    output reg [1:0] memBank,
    output reg invAddr
);

// Global = 0x10010000 - 0x10011000
// Stack = 0x7FFFEFFC - 0x7FFFFFFC

//reg [31:0] physicalAddrWire;
//assign physAddr = physicalAddrWire[12:2];

wire [10:0] globalAddress;
assign globalAddress = virtualAddr[12:2]; 

wire [10:0] stackAddress;
assign stackAddress = virtualAddr[12:2] + 10'd1;

wire [10:0] VGAAddress;
assign VGAAddress = (virtualAddr[12:2] - 11'h600);


always @(*)
begin
    if (!memWrite & !memRead)
    begin
        invAddr = 0;
        physAddr = 0;
        memEn = 0;
        memBank = 0;
    end
    else
    begin
        if ((virtualAddr < 32'hB800) || (virtualAddr >= 32'hCACF && virtualAddr < 32'h10010000) || (virtualAddr >= 32'h10011000 && virtualAddr < 32'hFFFF0000) || (virtualAddr >= 32'hFFFF000C && virtualAddr < 32'h7FFFEFFC) || (virtualAddr >= 32'h7FFFFFFC))
            begin
                invAddr = 1'd1;
                physAddr = 11'h0;
                memEn = 0;
                memBank = 0;
            end
        else
            begin
                if (virtualAddr >= 32'h7FFFEFFC && virtualAddr < 32'h7FFFFFFC)
                begin
                    invAddr = 1'd0;
                    physAddr = stackAddress;
                    memEn = 3'b001;
                    memBank = 2'd0;
                end
                else if (virtualAddr >= 32'h10010000 && virtualAddr < 32'h10011000)
                begin
                    invAddr = 1'd0;
                    physAddr = globalAddress;
                    memEn = 3'b001;
                    memBank = 2'd0;
                end
                else if(virtualAddr >= 32'hB800 && virtualAddr < 32'hCACF)
                begin
                    invAddr = 0;
                    physAddr = VGAAddress;
                    memEn = 3'b010;
                    memBank = 2'd1;
                end
                else if(virtualAddr >= 32'hFFFF0000 && virtualAddr < 32'hFFFF000C) //IO
                begin
                    invAddr = 0;
                    physAddr = 0;
                    memEn = 3'b100;
                    memBank = 2'd2;
                end
                else if(virtualAddr == 32'hFFFF0008)
                begin
                    invAddr = 0;
                    physAddr = 1;
                    memEn = 3'b100;
                    memBank = 2'd2;
                end
                else
                begin
                    invAddr = 1'h0;
                    physAddr = 11'h0;
                    memEn = 0;
                    memBank = 0;
                end
            end
    end
    
end
endmodule