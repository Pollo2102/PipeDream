/* verilator lint_off UNUSED */
/* verilator lint_off UNDRIVEN */
/*!
 * Milliseconds counter component.
 * @class MyCounter
 * @create msCounter_create
 * @eval msCounter_eval
 */
module MillisCounter(
    input clk, //! Assumes a 50MHz
    input reset,
    output [31:0] counter
);

`ifdef verilator
import "DPI-C" function int millis ();
`endif

    reg [15:0] cycle_count; // CPU cycle counter
    reg [31:0] ms_count;    // Millisecond counter

    assign counter = ms_count;

`ifdef verilator
    always @ (posedge clk)
        ms_count <= $c("millis()");
`else
    always @ (posedge clk) begin
        if (reset) begin
            cycle_count <= 16'h0;
            ms_count <= 32'h0;
        end
        else begin
            cycle_count <= cycle_count + 1'b1;
            if (cycle_count == 16'd50000)
            begin
                ms_count <= ms_count + 1;
                cycle_count <= 'h0;
            end
        end
    end
`endif

endmodule
