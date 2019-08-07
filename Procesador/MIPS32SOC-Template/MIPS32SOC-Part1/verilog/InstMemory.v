module InstMemory (
  input [7:0] addr,
  input en,
  output [31:0] readData
);
  reg [31:0] memory[0:255] /*verilator public*/;

  assign readData = en? memory[addr] : 32'hz;
  
  initial begin
`ifndef NO_INIT_MEM
    $readmemh("code.mif", memory, 0, 255);
`endif
  end
endmodule 
 
