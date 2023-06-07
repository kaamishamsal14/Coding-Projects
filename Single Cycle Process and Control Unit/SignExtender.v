`timescale 1ns / 1ps
module SignExtender(BusImm, Imm26, Ctrl); 
   output reg [63:0] BusImm; 
   input [25:0]  Imm26; 
   input [2:0]	 Ctrl; 
   
   reg extBit; 
   //no opcode from input, simply select instr
   //type from ctrl signal
   //ctrl assignments
   //I-type -> 000
   //D-type -> 001
   //CBZ    -> 010
   //B-type -> 011
   //MOVZ   -> 111 
   //ctrl now 3 bits updated control and processor

   always @(Imm26, Ctrl)
   begin
   if(Ctrl == 3'b000) // I Type, always extends zero
   
   begin
		extBit = 0;
		BusImm = {{52{extBit}}, Imm26[21:10]}; 
   end
   
   else if(Ctrl == 3'b001) //D type
   begin
		extBit = Imm26[20];
		BusImm = {{55{extBit}}, Imm26[20:12]};
   end
   
   else if(Ctrl == 3'b011) //b type
   begin
		extBit = Imm26[25];
		BusImm = {{38{extBit}}, Imm26[25:0]};
   end
   
   else if(Ctrl == 3'b010) // cbz
   begin
		extBit = Imm26[23];
		BusImm = {{45{extBit}}, Imm26[23:5]};
   end
   else if(Ctrl == 3'b111) // MOVZ
   begin
		//extBit =1'b0;
		//handle lsl with bits 22:21 of inst
		//00->0 shift, 01->16 bits, 10->32 , 11->48
		if(Imm26[22:21] == 2'b00)
			begin
				BusImm = {{48{1'b0}}, Imm26[20:5]};
			end
		else if(Imm26[22:21] == 2'b01)
			begin
				BusImm = {{32'b0}, Imm26[20:5],{16'b0}};
			end
		else if(Imm26[22:21] == 2'b10)
			begin
				BusImm = {{16'b0}, Imm26[20:5],{32'b0}};

			end
		else if(Imm26[22:21] == 2'b11)
			begin
				BusImm = {Imm26[20:5],{48{1'b0}}};
			end
	
   
   end	
		
		

   end
   
   
endmodule
