module RomColorPalette (
    input  [3:0] addr1,
    input  [3:0] addr2,
    output [7:0] color1,
    output [7:0] color2
);

    reg[7:0] memory[0:15]  /*verilator public*/;

    assign color1 = memory[addr1];
    assign color2 = memory[addr2];

    initial begin
        memory[0] = 8'b00000000; // Black
        memory[1] = 8'b00000010; // Blue
        memory[2] = 8'b00010100; // Green
        memory[3] = 8'b00010110; // Cyan
        memory[4] = 8'b10100000; // Red
        memory[5] = 8'b10100010; // Magenta
        memory[6] = 8'b10101000; // Brown
        memory[7] = 8'b10110110; // White
        memory[8] = 8'b01001001; // Grey
        memory[9] = 8'b01001011; // Light blue
        memory[10] = 8'b01011101; // Light green
        memory[11] = 8'b01011111; // Light cyan
        memory[12] = 8'b11101001; // Light red
        memory[13] = 8'b11101011; // Light magenta
        memory[14] = 8'b11111101; // Yellow
        memory[15] = 8'b11111111; // Bright white
    end
endmodule // RomColorPalette
