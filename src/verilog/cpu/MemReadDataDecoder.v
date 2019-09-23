module MemReadDataDecoder(
    input [31:0] inData,
    input [1:0] offset,
    input bitExt, // 0 sign extend, 1 zero extend
    input [1:0]dataSize, // 0 word, 1 half, 2 byte
    output reg [31:0] outData
);

always @(*)
begin
    if (dataSize == 0) // LW
    begin
        outData = inData;
    end
    else if (dataSize == 1) // LH
    begin
        if (offset == 0)
        begin
            outData = (bitExt) ? {16'd0, inData[31:16]} : {{16{inData[31]}}, inData[31:16]};
        end
        else if (offset == 2)
        begin
            outData = (bitExt) ? {16'd0, inData[15:0]} : {{16{inData[15]}}, inData[15:0]};
        end
        else begin
            outData = 32'h0;
        end
    end
    else if(dataSize == 2)  // LB
    begin
        if (offset == 0)
        begin
            outData = (bitExt) ? {24'd0, inData[31:24]} : {{24{inData[31]}}, inData[31:24]};
        end
        else if (offset == 1)
        begin
            outData = (bitExt) ? {24'd0, inData[23:16]} : {{24{inData[23]}}, inData[23:16]};
        end
        else if (offset == 2)
        begin
            outData = (bitExt) ? {24'd0, inData[15:8]} : {{24{inData[15]}}, inData[15:8]};
        end
        else
        begin
            outData = (bitExt) ? {24'd0, inData[7:0]} : {{24{inData[7]}}, inData[7:0]};
        end
    end
end

endmodule