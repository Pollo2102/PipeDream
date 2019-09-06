module DataMemory(
    input clk, //! Clock
    input en, //! Chip Enable
    input [3:0] memWrite, //! Write Enable Bitmap
    input [10:0] addr, //! Address to Read/Write
    input [31:0] wdata, //! Write Data
    output reg [31:0] rdata //! Read Data
);
 
    reg [31:0] memory[0:2047] /*verilator public*/;
   
    assign rdata = en? memory[addr] : 32'hz;
 
    always @(posedge clk)
    begin
        if (en) begin
            if (memWrite[3]) memory[addr][7:0] <= wdata[7:0];
            if (memWrite[2]) memory[addr][15:8] <= wdata[15:8];
            if (memWrite[1]) memory[addr][23:16] <= wdata[23:16];
            if (memWrite[0]) memory[addr][31:24] <= wdata[31:24];
        end
    end
 
    initial begin
`ifndef NO_INIT_MEM
        $readmemh("data.mif", memory, 0, 2047);
`endif
    end
endmodule