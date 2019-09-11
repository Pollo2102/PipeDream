module DualPortVGARam (
    input clka,
    input enablea,
    input [3:0] wea,
    input [10:0] addra,
    input [31:0] wda,
    output reg [31:0] rda,
    input clkb,
    input[10:0] addrb,
    output reg [31:0] rdb
);

    reg [31:0] memory [0:2047] /*verilator public*/;

    assign rda = enablea? memory[addra] : 32'hz;

    always @ (posedge clka)
    begin
        if (enablea) begin
            if (wea[3]) memory[addra][7:0] <= wda[7:0];
            if (wea[2]) memory[addra][15:8] <= wda[15:8];
            if (wea[1]) memory[addra][23:16] <= wda[23:16];
            if (wea[0]) memory[addra][31:24] <= wda[31:24];
        end
    end

    always @ (posedge clkb)
    begin
        rdb <= memory[addrb];
    end
    
    initial begin
`ifdef VGA_RAM_INIT
        $readmemh("vga_ram.mif", memory, 0, 2047);
`endif
    end
endmodule
