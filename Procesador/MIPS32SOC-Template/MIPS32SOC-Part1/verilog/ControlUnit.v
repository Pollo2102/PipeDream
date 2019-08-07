`include "alu_defines.vh"
`include "mips32_opcodes.vh" 

module ControlUnit(
    input [5:0] opc, //! Opcode
    input [5:0] func, //! Function
    output isJmp, //! Jump signal
    output isBeq, //! BEQ signal
    output isBne, //! BNE signal
    output [1:0] rfWriteDataSel, //! Register File Write Data Select
    output rfWriteAddrSel, //! Register File Write Address Select
    output rfWriteEnable, //! Register Write Enable
    output memWrite, //! Memory Write
    output memRead, //! Memory Read
    output aluSrc, //! ALU source
    output [2:0] aluFunc, //! ALU operation
    output bitXtend, //! Bit extension, 0 = sign extend, 1 = zero extend
    output invOpcode //! Invalid opcode or function
);

always @(*)
begin
    isJmp = 1'd0;
    isBeq = 1'd0;
    isBne = 1'd0;
    rfWriteAddrSel = 1'd0;
    rfWriteDataSel = 1'd0;
    rfWriteEnable = 1'd0;
    memWrite = 1'd0;
    memRead = 1'd0;
    aluSrc = 1'd0;
    aluFunc = 3'd0;
    bitXtend = 1'd0;
    invOpcode = 1'd0;

    if(opc == 0)
    begin
        case (func)
            `MIPS_ADD:
            begin
                rfWriteAddrSel = 1'd1;
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_ADD;
            end 
            `MIPS_SUB:
            begin
                rfWriteAddrSel = 1'd1;
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_SUB;
            end 
            `MIPS_AND:
            begin
                rfWriteAddrSel = 1'd1;
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_AND;
            end 
            `MIPS_OR:
            begin
                rfWriteAddrSel = 1'd1;
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_OR;
            end 
            `MIPS_SLT:
            begin
                rfWriteAddrSel = 1'd1;
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_SLT;
            end 
        endcase
    end
    else
    begin
        case (opc)
            `MIPS_LW:
            begin
                rfWriteDataSel = 1'd1;
                rfWriteEnable = 1'd1;
                memRead = 1'd1;
                aluSrc = 1'd1;
                aluFunc = `ALU_ADD;
            end        
            `MIPS_SW:
            begin
                memWrite = 1'd1;
                aluSrc = 1'd1;
                aluFunc = `ALU_ADD;
            end        
            `MIPS_BEQ:
            begin
                isBeq = 1'd1;
                aluFunc = `ALU_SUB;
            end        
            `MIPS_BNE:
            begin
                isBne = 1'd1;
                aluFunc = `ALU_SUB;
            end        
            `MIPS_JUMP:
            begin
                isJmp = 1'd1;
            end        
        endcase
    end
end

endmodule

