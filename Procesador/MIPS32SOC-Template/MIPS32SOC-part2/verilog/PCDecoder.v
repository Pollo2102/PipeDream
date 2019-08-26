module PCDecoder(
    input [31:0] VirtualPC,
    output [9:0] PhysicalPC,
    output InvalidPC
);

always @(*)
begin
    if (VirtualPC < 32'h400000 || VirtualPC > 32'h401000)
    begin
        InvalidPC = 1'd1;
        PhysicalPC = 10'hx;
    end
    else
    begin
        PhysicalPC = VirtualPC[11:2];
        InvalidPC = 1'd0;
    end
end
endmodule