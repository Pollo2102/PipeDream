module InstMemory (
  input [10:0] addr,
  input en,
  input clk,
  output reg [31:0] readData
);
  reg [31:0] memory[0:2047] /*verilator public*/;

  always @(posedge clk)
  begin
    readData = en? memory[addr] : 32'hz;
  end
  
  initial begin
`ifndef NO_INIT_MEM
    $readmemh("code.mif", memory, 0, 255);
`endif
  end
endmodule 
 
