`include "alu_defines.vh"
`include "mips32_opcodes.vh" 

module ControlUnit(
    input [5:0] opc, //! Opcode
    input [5:0] func, //! Function
    input rt,
    output reg isJmp, //! Jump signal
    output reg [2:0] branch,
    output reg [1:0] rfWriteDataSel, //! Register File Write Data Select
    output reg rfWriteAddrSel, //! Register File Write Address Select
    output reg rfWriteEnable, //! Register Write Enable
    output reg memWrite, //! Memory Write
    output reg memRead, //! Memory Read
    output reg [1:0] aluSrc, //! ALU source
    output reg aluSrc2,
    output reg [3:0] aluFunc, //! ALU operation
    output reg bitXtend, //! Bit extension, 0 = sign extend, 1 = zero extend
    output reg [1:0] memDataSize,
    output reg memBitExt,
    output reg isJR,
    output reg isJAL,
    output reg invOpcode //! Invalid opcode or function
);

always @(*)
begin
    isJmp = 1'd0;
    branch = 3'd0;
    rfWriteAddrSel = 1'd0;
    rfWriteDataSel = 2'd0;
    rfWriteEnable = 1'd0;
    memWrite = 1'd0;
    memRead = 1'd0;
    aluSrc = 2'd0;
    aluSrc2 = 1'd0;
    aluFunc = 4'd0;
    bitXtend = 1'd0;
    memDataSize = 2'd0;
    memBitExt = 1'd0;
    isJR = 1'd0;
    isJAL = 1'd0;
    invOpcode = 1'd0;

    if(opc == 0)
    begin
        case (func)
            `MIPS_SLL:
            begin
                rfWriteAddrSel = 1'd1;
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_SLL;
                aluSrc = 2'd2;
                aluSrc2 = 1'd1;
            end
            `MIPS_SRL:
            begin
                rfWriteAddrSel = 1'd1;
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_SRL;
                aluSrc = 2'd2;
                aluSrc2 = 1'd1;
            end
            `MIPS_SRA:
            begin
                rfWriteAddrSel = 1'd1;
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_SRA;
                aluSrc = 2'd2;
                aluSrc2 = 1'd1;
            end
            `MIPS_SLLV:
            begin
                rfWriteAddrSel = 1'd1;
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_SLL;
                aluSrc = 2'd3;
                aluSrc2 = 1'd1;
            end
            `MIPS_SRLV:
            begin
                rfWriteAddrSel = 1'd1;
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_SRL;
                aluSrc = 2'd3;
                aluSrc2 = 1'd1;
            end
            `MIPS_SRAV:
            begin
                rfWriteAddrSel = 1'd1;
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_SRA;
                aluSrc = 2'd3;
                aluSrc2 = 1'd1;
            end
            `MIPS_ADD:
            begin
                rfWriteAddrSel = 1'd1;
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_ADD;
            end 
            `MIPS_ADDU:
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
            `MIPS_SUBU:
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
            `MIPS_XOR:
            begin
                rfWriteAddrSel = 1'd1;
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_XOR;
            end
            `MIPS_SLT:
            begin
                rfWriteAddrSel = 1'd1;
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_SLT;
            end 
            `MIPS_SLTU:
            begin
                rfWriteAddrSel = 1'd1;
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_SLTU;
            end 
            `MIPS_JR:
            begin
                isJR = 1'd1;
            end
            default:
            begin
                invOpcode = 1'd1;
            end
        endcase
    end
    else
    begin
        case (opc)
            `MIPS_ADDI:
            begin
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_ADD;
                aluSrc = 2'd1;
            end 
            `MIPS_ADDIU:
            begin
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_ADD;
                aluSrc = 2'd1;
            end
            `MIPS_ANDI:
            begin
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_AND;
                aluSrc = 2'd1;
                bitXtend = 1'd1;
            end
            `MIPS_ORI:
            begin
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_OR;
                aluSrc = 2'd1;
                bitXtend = 1'd1;
            end
            `MIPS_XORI:
            begin
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_XOR;
                aluSrc = 2'd1;
                bitXtend = 1'd1;
            end
            `MIPS_LUI:
            begin
                rfWriteDataSel = 2'b10;
                rfWriteEnable = 1'd1;
            end
            `MIPS_SLTI:
            begin
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_SLT;
                aluSrc = 2'd1;
            end 
            `MIPS_SLTIU:
            begin
                rfWriteEnable = 1'd1;
                aluFunc = `ALU_SLTU;
                aluSrc = 2'd1;
            end 
            `MIPS_LW:
            begin
                rfWriteDataSel = 2'd1;
                rfWriteEnable = 1'd1;
                memRead = 1'd1;
                aluSrc = 2'd1;
                aluFunc = `ALU_ADD;
            end     
            `MIPS_LH: // Part3
            begin
                rfWriteDataSel = 2'd1;
                rfWriteEnable = 1'd1;
                memRead = 1'd1;
                memDataSize = 2'd1;
                aluSrc = 2'd1;
                aluFunc = `ALU_ADD;
            end  
            `MIPS_LHU: // Part3
            begin
                rfWriteDataSel = 2'd1;
                rfWriteEnable = 1'd1;
                memRead = 1'd1;
                memDataSize = 2'd1;
                memBitExt = 1'd1;
                aluSrc = 2'd1;
                aluFunc = `ALU_ADD;
            end  
            `MIPS_LB: // Part3
            begin
                rfWriteDataSel = 2'd1;
                rfWriteEnable = 1'd1;
                memRead = 1'd1;
                memDataSize = 2'd2;
                aluSrc = 2'd1;
                aluFunc = `ALU_ADD;
            end
            `MIPS_LBU: // Part3
            begin
                rfWriteDataSel = 2'd1;
                rfWriteEnable = 1'd1;
                memRead = 1'd1;
                memDataSize = 2'd2;
                memBitExt = 1'd1;
                aluSrc = 2'd1;
                aluFunc = `ALU_ADD;
            end 
            `MIPS_SW:
            begin
                memWrite = 1'd1;
                aluSrc = 2'd1;
                aluFunc = `ALU_ADD;
            end     
            `MIPS_SH: // Part3
            begin
                memWrite = 1'd1;
                memDataSize = 2'd1;
                aluSrc = 2'd1;
                aluFunc = `ALU_ADD;
            end     
            `MIPS_SB: // Part3
            begin
                memWrite = 1'd1;
                memDataSize = 2'd2;
                aluSrc = 2'd1;
                aluFunc = `ALU_ADD;
            end   
            `MIPS_BEQ:
            begin
                branch = 3'd1;
                aluFunc = `ALU_SUB;
            end        
            `MIPS_BGEZ:
            begin
                branch = rt ? 3'd3 : 3'd6;
                aluFunc = `ALU_SUB;
            end
            `MIPS_BGTZ:
            begin
                branch = 3'd4;
                aluFunc = `ALU_SUB;
            end
            `MIPS_BLEZ:
            begin
                branch = 3'd5;
                aluFunc = `ALU_SUB;
            end
            `MIPS_BNE:
            begin
                branch = 3'd2;
                aluFunc = `ALU_SUB;
            end        
            `MIPS_JUMP:
            begin
                isJmp = 1'd1;
            end
            `MIPS_JAL:
            begin
                isJAL = 1'd1;
                rfWriteDataSel = 2'd3;
                rfWriteEnable = 1'd1;
            end
            default:  
            begin
                invOpcode = 1'd1;
            end
        endcase
    end
end

endmodule

