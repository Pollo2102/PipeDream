/*!
 * Register file 2 read ports 1 write port.
 * @type ram
 * @size 32
 */
module RegisterFile(
    input [4:0] ra1,
    input [4:0] ra2,
    input [4:0] wa,
    input [31:0] wd,
    input we,
    input clk,
    output [31:0] rd1,
    output [31:0] rd2
    );

    reg [31:0] memory[0:31] /*verilator public*/;
    
    assign rd1 = memory[ra1];
    assign rd2 = memory[ra2];
    
    always @(posedge clk)
    begin
        if (we && (wa != 5'd0))
            memory[wa] <= wd;
        else
            memory[wa] <= memory[wa];
    end

    initial begin
        memory[0] = 32'd0;
    end
endmodule
