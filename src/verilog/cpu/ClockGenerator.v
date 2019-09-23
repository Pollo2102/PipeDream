module ClockGenerator (
    input clkIn,  //! Clock input. On MimasV2 this is 100mhz
    output fastClk, //! Data Memory clock 50Mhz
    output vgaClk, //! VGA clock 25mhz
    output reg slowClk //! CPU clock (Freq is 1/2 of Data Memory Clock)
);

`ifdef SYNTHESIS
    /*
     * During synthesis we use the Digital Clock Manager
     * of the FPGA to generate a stable main clock signal 
     * and a VGA clock signal
     */
    // 50mhz CLOCK
    DCM_SP #(.CLKFX_DIVIDE(4), .CLKFX_MULTIPLY(2), .CLKIN_PERIOD(10))
            cpu_dcm (
                .CLKIN(clkIn),
                .CLKFX(fastClk),
                .CLKFB(1'b0),
                .PSEN(1'b0),
                .RST(1'b0)
            );

    // VGA clock is 25mhz
    DCM_SP #(.CLKFX_DIVIDE(8), .CLKFX_MULTIPLY(2), .CLKIN_PERIOD(10))
            vga_dcm (
                .CLKIN(clkIn),
                .CLKFX(vgaClk),
                .CLKFB(1'b0),
                .PSEN(1'b0),
                .RST(1'b0)
            );

`else
    assign fastClk = clkIn;
    assign vgaClk = clkIn;
`endif

always @ (posedge fastClk)
    slowClk <= !slowClk;

initial
    slowClk = 0;

endmodule
