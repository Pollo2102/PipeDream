module MemWriteDataEncoder(
    input [31:0] inData,
    input [1:0] offset,
    input memWrite,
    input [1:0] dataSize,
    output [31:0] outData,
    output [3:0] encMW
);

always @(*)
begin
    if (!memWrite)
    begin
        encMW = 4'd0;
        outData = 32'd0;
    end
    else
    begin
        if (dataSize == 0) // SW
        begin
            outData = inData;
            encMW = 4'b1111;;
        end
        else if (dataSize == 1) // SH
        begin
            if (offset == 0)
            begin
                outData = {inData[15:0], 16'd0};
                encMW = 4'b0011;
            end
            else if (offset == 2)
            begin
                outData = {16'd0, inData[15:0]};
                encMW = 4'b1100;
            end
            else begin
                outData = 32'h0;
                encMW = 4'd0;
            end
        end
        else if(dataSize == 2)  // SB
        begin
            if (offset == 0)
            begin
                outData = {inData[7:0], 24'd0};
                encMW = 4'b0001;
            end
            else if (offset == 1)
            begin
                outData = {8'd0, inData[7:0], 16'd0};
                encMW = 4'b0010;
            end
            else if (offset == 2)
            begin
                outData = {16'd0, inData[7:0], 8'd0};
                encMW = 4'b0100;
            end
            else
            begin
                outData = {24'd0, inData[7:0]};
                encMW = 4'b1000;
            end
        end
    end
end


endmodule