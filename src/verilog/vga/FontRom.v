/* verilator lint_off UNDRIVEN */
module FontRom (
    input clk,
    input [11:0] addr,
    output reg [7:0] dout
);

    reg[7:0] memory[0:4095] /*verilator public*/;

    always @(posedge clk) begin
        dout <= memory[addr];
    end

    initial begin
`ifndef NO_INIT_MEM    
        $readmemh("font_rom.mif", memory, 0, 4095);
`endif
    end
endmodule
