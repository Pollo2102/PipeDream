/* verilator lint_off WIDTH */
module VGA80X30Color(
    input clk,  // 25 Mhz for 640x480 resolution
    input reset,
    output [10:0] vgaram_addr,  // vga memory address
    input [31:0] vgaram_data,   // vga memory data
    output [11:0] fontrom_addr, // Font ROM address
    input [7:0] fontrom_data,   // Font ROM data
    output [3:0] palrom_addr1,  // Palette ROM address 1
    output [3:0] palrom_addr2,  // Palette ROM address 2
    input [7:0] palrom_data1,   // Palette ROM data 1
    input [7:0] palrom_data2,   // Palette ROM data 2
    output reg [2:0] red,
    output reg [2:0] green,
    output reg [1:0] blue,
    output reg hsync,
    output reg vsync
);

    reg [9:0] hcount;
    reg [9:0] vcount;

    wire [4:0] scr_row; // Screen row (0 to 29)
    wire [6:0] scr_col; // Screen column (0 to 79)
    wire [3:0] chr_row; // Character row (0 to 15)
    wire [2:0] chr_col; // Character column (0 to 7)
    wire [7:0] chr_index;
    wire [11:0] symb_index; // The index of the current symbol to display
    wire [15:0] symb_data; // The data of the current symbol to display
    reg  [7:0] fg_color; // Foreground color
    reg  [7:0] bg_color; // Background color
    reg  [7:0] chr_data;

    assign symb_data = (symb_index[0] == 1'b0)? vgaram_data[31:16] : vgaram_data[15:0]; 
    assign chr_index = symb_data[7:0];
    assign scr_row = vcount[8:4]; // divide by 16
    assign scr_col = hcount[9:3]; // divide by 8

    assign palrom_addr1 = symb_data[15:12];
    assign palrom_addr2 = symb_data[11:8];
    assign chr_row = vcount[3:0]; // mod 16
    assign chr_col = ~hcount[2:0]; // mod 8 (Inverted 'cause columns go from 7 to 0 in the ROM)
    assign symb_index = scr_row * 80 + {7'h00, scr_col};
    assign fontrom_addr = chr_index * 16 + {8'h00, chr_row};
    assign vgaram_addr = symb_index[11:1]; // Divide by 2

    always @ (posedge clk)
    begin
      if (chr_col == 3'h0) begin
          chr_data <= fontrom_data;
          bg_color <= palrom_data1;
          fg_color <= palrom_data2;
      end
    end

    always @ (posedge clk)
    begin
        if (reset) begin
            hcount <= 10'h0;
            vcount <= 10'h0;
        end
        else begin
            if (hcount == 799) begin
                hcount <= 0;

                if (vcount == 524)
                    vcount <= 0;
                else
                    vcount <= vcount + 1;
            end
            else
                hcount <= hcount + 1;

            if ((vcount >= 490) && (vcount < 492))
                vsync <= 0; //Vertical sync pulse
            else
                vsync <= 1;

            if ((hcount >= 656) && (hcount < 752))
                hsync <= 0; //Horizontal sync pulse
            else
                hsync <= 1;

            if (((hcount > 7) && (hcount < 648)) && (vcount < 480))
            begin
                if (chr_data[chr_col] == 1'b1)
                    {red, green, blue} <= fg_color;
                else
                    {red, green, blue} <= bg_color;
            end
            else begin
                {red, green, blue} <= 8'h0;
            end
        end
    end
endmodule
