`timescale 1ns / 1ps
module singlecycle(
		   input 	     	 resetl,
		   input [63:0]      startpc,
		   output reg [63:0] currentpc,
		   output [63:0]     MemtoRegOut,  // this should be
						   // attached to the
						   // output of the
						   // MemtoReg Mux
		   input 	     CLK
		   );

   // Next PC connections
   wire [63:0] 			     nextpc;       // The next PC, to be updated on clock cycle

   // Instruction Memory connections
   wire [31:0] 			     instruction;  // The current instruction

   // Parts of instruction
   wire [4:0] 			     rd;            // The destination register
   wire [4:0] 			     rm;            // Operand 1
   wire [4:0] 			     rn;            // Operand 2
   wire [10:0] 			     opcode;
   //wire [5:0]			     shamt;

   // Control wires
   wire 			     reg2loc;
   wire 			     alusrc;
   wire 			     mem2reg;
   wire 			     regwrite;
   wire 			     memread;
   wire 			     memwrite;
   wire 			     branch;
   wire 			     uncond_branch;
   wire [3:0] 			 aluctrl;
   wire [2:0] 			 signop;

   // Register file connections
   wire [63:0] 			     regoutA;     // Output A
   wire [63:0] 			     regoutB;     // Output B

   // ALU connections
   wire [63:0] 			     aluout;
   wire 			     	 zero;

   // Sign Extender connections
   wire [63:0] 			     extimm;
	
	

	
	
	
   // PC update logic
   always @(negedge CLK)
     begin
        if (resetl)
          currentpc <= #3 nextpc;
        else
          currentpc <= #3 startpc;
     end
	 
	NextPClogic nextPC(
		.NextPC(nextpc),
		.CurrentPC(currentpc),
		.SignExtImm64(extimm),
		.Branch(branch),
		.ALUZero(zero),
		.Uncondbranch(uncond_branch)
		);
	

   // Parts of instruction
   assign rd = instruction[4:0];
   assign rm = instruction[9:5];
   assign rn = reg2loc ? instruction[4:0] : instruction[20:16];
   assign opcode = instruction[31:21];

   InstructionMemory imem(
			  .Data(instruction),
			  .Address(currentpc)
			  );

   control control(
		   .reg2loc(reg2loc),
		   .alusrc(alusrc),
		   .mem2reg(mem2reg),
		   .regwrite(regwrite),
		   .memread(memread),
		   .memwrite(memwrite),
		   .branch(branch),
		   .uncond_branch(uncond_branch),
		   .aluop(aluctrl),
		   .signop(signop),
		   .opcode(opcode)
		   );
		   
	/*
    * Connect the remaining datapath elements below.
    * Do not forget any additional multiplexers that may be required.
    */
	//look at single cycle processor graph and connect things together

	ALU alu(
		.BusW(aluout),
		.BusA(regoutA), //input of BusA of ALU is from output of register A
		.BusB(alusrc ? extimm : regoutB), //input of BusB of ALU has a mux with regoutB and signextend, determined by ALUSRC
										  //alusrc = 1 -> extimm else regoutB
		.ALUCtrl(aluctrl),
		.Zero(zero)
		//.SHAMT(shamt)
		);
		
	SignExtender signextender(
		.BusImm(extimm),
		.Imm26(instruction[25:0]), //need to adjust for 26 bits??
		.Ctrl(signop)
		);

	RegisterFile registerfile(
		.BusA(regoutA), //output
		.BusB(regoutB), //output
		.BusW(mem2reg ? MemtoRegOut:aluout), //mux with readData when 1, Aluout when 0, controlled by MemtoReg
		.RA(rm),
		.RB(rn),
		.RW(rd),
		.RegWr(regwrite), 
		.Clk(CLK)
		);
	
	DataMemory datamemory(
		.ReadData(MemtoRegOut),
		.Address(aluout),
		.WriteData(regoutB),
		.MemoryRead(memread),
		.MemoryWrite(memwrite),
		.Clock(CLK)
		);
		




endmodule

