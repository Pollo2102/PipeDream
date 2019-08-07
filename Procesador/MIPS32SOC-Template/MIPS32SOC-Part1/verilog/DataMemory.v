module DataMemory (
  input [7:0] addr,
  input [31:0] writeData,
  input memWrite,
  input clk,
  input memRead,
  output [31:0] readData
);
  reg [31:0] memory[0:255] /*verilator public*/;

  assign readData = memRead? memory[addr] : 32'hz;

  always @ (posedge clk) begin
    if (memWrite)
      memory[addr] <= writeData;
  end

  initial begin
`ifndef NO_INIT_MEM
    $readmemh("data.mif", memory, 0, 255);
`endif
  end
endmodule 
