/* verilator lint_off UNUSED */
module MIPS32SOC (
    input clk, // Clock signal
    input resetIn,  // Reset signal
    input [7:0] keypadIn,
    output [2:0]red,
    output [2:0]green,
    output [1:0]blue,
    output hsync,
    output vsync,
    output invalidPC,
    output invalidOpc,
    output invalidAddr
);
    wire reset;
    wire [7:0]keypad;

    `ifdef SYNTHESIS
      assign reset = ~resetIn;
      assign keypad = ~keypadIn;
    `else
      assign reset = resetIn;
      assign keypad = keypadIn;
    `endif

    wire fastClk;
    wire vgaClk;
    wire slowClk;
    wire [1:0] memBank;
    wire [31:0]counter;
    wire [31:0] inst /*verilator public*/;
    reg  [31:0] nextPC/* verilator public */; // Should be 'reg' because it used in a always block
    reg  [31:0] PC /*verilator public*/; // The PC (Program Counter) register
    wire [10:0] physPC; // Physical PC from the PCDecoder
    wire [31:0] pcPlus4;
    wire [5:0] func;
    wire [4:0] rd /*verilator public*/;
    wire [4:0] rt /*verilator public*/;
    wire [4:0] rs /*verilator public*/;
    wire [5:0] opcode;
    wire [1:0] aluSrc/* verilator public */;
    wire rfWriteEnable; // Register File Write Enable
    wire rfWriteAddrSel; // Register File Write Address Select
    wire [1:0] rfWriteDataSel; // Register File Write Data Select
    wire [4:0] rfWriteAddr; // Register File Write Address
    reg  [31:0] rfWriteData; // Register File Write Data
    wire [31:0] rfData1 /*verilator public*/;
    wire [31:0] rfData2 /*verilator public*/;
    wire [31:0] imm32;
    wire [15:0] imm16;
    wire [31:0] memAddr/* verilator public */;
    wire [10:0] PhysicalAddress /* verilator public */;
    wire memWrite;
    wire memRead;
    wire [1:0] memDataSize;
    wire memBitExt;
    wire [31:0] decodedData;
    wire [3:0] encMW;
    reg [31:0] memData;
    wire [3:0] aluFunc;
    reg [31:0] aluOperand2/* verilator public */;
    wire [31:0] aluResult/* verilator public */;
    wire [31:0] branchTargetAddr;
    wire [31:0] jmpTarget32;
    wire isJmp /*verilator public*/;
    wire isBeq /*verilator public*/;
    wire isBne /*verilator public*/;
    wire isZero /*verilator public*/;
    wire bitXtend;
    wire [2:0] memEnable /* verilator public */;
    wire isJR;
    wire isJAL;
    wire invalidOpcode /*verilator public*/;
    // wire invalidPC /* verilator public */;
    // wire invalidAddr /* verilator public */;
    wire [4:0] raAddr;
    wire [31:0] decodedMemData;
    wire [4:0 ]shamt;
    wire aluSrc2/* verilator public */;
    wire rfWEnable;
    wire [31:0] aluOp1/* verilator public */;
    wire branchTaken;
    wire [2:0] branch;
    wire [31:0] keypadOut /* verilator public */;
    wire [31:0]keypadIn2 /* verilator public */;

  
    assign keypadIn2 = {keypad, 24'd0};
    assign invalidOpc = invalidOpcode;
    assign raAddr = (isJAL) ? 5'd31 : rfWriteAddr;
    assign func = inst[5:0];
    assign rfWEnable = reset ? 1'd0 : rfWriteEnable;
    assign rd = inst[15:11];
    assign rt = inst[20:16];
    assign rs = inst[25:21];
    assign opcode = inst[31:26];
    assign imm16 = inst[15:0];
    assign memAddr = aluResult;
    assign shamt = inst[10:6];

    assign pcPlus4 = PC + 32'd4;
    assign jmpTarget32 = {pcPlus4[31:28], inst[25:0], 2'b00};
    assign branchTargetAddr = pcPlus4 + {imm32[29:0], 2'b00};

    assign rfWriteAddr = rfWriteAddrSel? rd : rt; // MUX
    //assign aluOperand2 = aluSrc? imm32 : rfData2; // MUX
    assign aluOp1 = (aluSrc2) ? rfData2 : rfData1;
    //assign rfWriteData = rfWriteDataSel[0]? memData : aluResult; // MU

    always @(*)
    begin
      case (aluSrc)
        2'b00: aluOperand2 = rfData2;
        2'b01: aluOperand2 = imm32;
        2'b10: aluOperand2 = {27'd0 ,shamt};
        2'b11: aluOperand2 = rfData1;
      endcase
    end

    always @(*)
    begin
      case (rfWriteDataSel)
        2'b00: rfWriteData = aluResult;
        2'b01: rfWriteData = decodedMemData;
        2'b10: rfWriteData = {imm16, 16'd0};
        2'b11: rfWriteData = pcPlus4;
      endcase
    end

    // Next PC value
    always @ (*) begin
        /* 
         * TODO: Compute next PC.  Take into account
         * the JMP, BEQ and BNE instructions
         */
          /* if (invalidAddr)
            nextPC = PC;
            nextPC = 32'h400000;
          else */ if (reset)
            nextPC = 32'h400000;
          else if (branchTaken)
            nextPC = branchTargetAddr;
          else if (isJmp || isJAL)
            nextPC = jmpTarget32;
          else if (isJR)
            nextPC = rfData1;
          else
            nextPC = pcPlus4;
    end
  
    // PC
    always @ (posedge slowClk) begin
        if (reset)
            PC <= 32'h400000;
        else if (invalidOpcode || invalidPC || invalidAddr)
            PC <= PC;
        else
            PC <= nextPC;
    end

    //PCDecoder
    PCDecoder PCDec (
        .VirtualPC( nextPC ),
        .PhysicalPC( physPC ),
        .InvalidPC( invalidPC )
    );
  
    // Instruction Memory
    InstMemory instMem (
        .clk( slowClk ),
        .addr( physPC ),
        .en( 1'b1 ),
        .readData( inst )
    );

    // Memory Decoder
    MemDecoder memDecoder (
        .virtualAddr( memAddr ),
        .memWrite( memWrite ),
        .memRead( memRead ),
        .physAddr( PhysicalAddress ),
        .memEn( memEnable ),
        .memBank( memBank ),
        .invAddr( invalidAddr )
    );

    wire [31:0] memData1;
    wire [31:0] memData2 /* verilator public */;

    always @(*)
    begin
      case (memBank)
        2'b00: memData = memData1;
        2'b01: memData = memData2;
        2'b10: memData = keypadOut;
        2'b11: memData = counter;
      endcase
    end

    MemWriteDataEncoder memWDataEnc(
        .inData( rfData2 ),
        .offset( imm32[1:0] ),
        .memWrite( memWrite ),
        .dataSize( memDataSize ),
        .outData( decodedData ),
        .encMW( encMW )
    );
    

    // Data Memory
    DataMemory dataMem (
        .clk( fastClk ),
        .en( memEnable[0] ),
        .memWrite( encMW ),
        .addr( PhysicalAddress ),
        .wdata( decodedData ),
        .rdata ( memData1 )
    );


    MemReadDataDecoder memRDataDec(
        .inData( memData ),
        .offset( imm32[1:0] ),
        .bitExt( memBitExt ),
        .dataSize( memDataSize ),
        .outData( decodedMemData )
    );

    
 
    //Register File
    RegisterFile regFile (
        .ra1( rs ),
        .ra2( rt ),
        .wa( raAddr ),
        .wd( rfWriteData ),
        .we( rfWEnable ),
        .clk( slowClk ),
        .rd1( rfData1 ),
        .rd2( rfData2 )
    );


  // ALU
  ALU alu (
    .a( aluOp1 ),
    .b( aluOperand2 ),
    .func( aluFunc ),
    .res( aluResult ),
    .isZero( isZero )
  );

  // BitExtender
  BitExtender BitExtender_i12 (
    .extend( bitXtend ),
    .in( imm16 ),
    .out( imm32 )
  );

  
  BranchResolver branchResolver(
    .branch(branch),
    .zero( isZero ),
    .sign( aluResult[31] ),
    .branchTaken( branchTaken )
  );
  

  // Control Unit
  ControlUnit controlUnit (
    .opc( opcode ),
    .func( func ),
    .rt(rt[0]),
    .isJmp( isJmp ),
    .branch( branch ),
    .rfWriteDataSel( rfWriteDataSel ),
    .rfWriteAddrSel( rfWriteAddrSel ),
    .rfWriteEnable( rfWriteEnable ),
    .memWrite( memWrite ),
    .memRead( memRead ),
    .aluSrc( aluSrc ),   
    .aluSrc2( aluSrc2 ), 
    .aluFunc( aluFunc ),
    .bitXtend( bitXtend ),
    .memDataSize( memDataSize ),
    .memBitExt( memBitExt ),
    .isJR( isJR ),
    .isJAL( isJAL ),
    .invOpcode( invalidOpcode )
  );

  VGATextCard vgaTextCard(
    .vclk( vgaClk ),
    .clk( fastClk ), // Verify
    .en( memEnable[1] ), 
    .reset( reset ), 
    .memWrite( encMW ), 
    .addr( PhysicalAddress ), 
    .wdata( decodedData ), 
    .rdata( memData2 ), 
    .red( red ), 
    .green( green ), 
    .blue( blue ), 
    .hsync( hsync ),  
    .vsync( vsync )
  );

  ClockGenerator clockGenerator(
    .clkIn( clk ),
    .fastClk( fastClk ),
    .vgaClk( vgaClk ),
    .slowClk( slowClk )
  );

  MillisCounter millisCounter(
    .clk( fastClk ),
    .counter( counter ),
    .reset( reset )
  );

  IOModule iomodule(
    .keypadIn( keypadIn2 ),
    /* .addr( PhysicalAddress[0] ), */
    .en( memEnable[2] ),
    .keypadOut( keypadOut )
  );
endmodule
