`timescale 1ns / 1ps
module NextPClogic(NextPC, CurrentPC, SignExtImm64, Branch, ALUZero, Uncondbranch); 
   input [63:0] CurrentPC, SignExtImm64; 
   input 	Branch, ALUZero, Uncondbranch; 
   output reg [63:0] NextPC; 

	reg [63:0] SignExtShift;
	reg BranchLogic;
	

   //branches when Branch -> CBZ true, UncondBranch is true
	always @(*) begin
	
	//cant just update original variable
	SignExtShift = SignExtImm64 << 2; 

	 
	BranchLogic = (Branch && ALUZero) || Uncondbranch;
	
	if(BranchLogic) begin
			NextPC = CurrentPC + SignExtShift;
	end
		
	else begin
		NextPC = CurrentPC + 4;

	end
	
	end





endmodule
