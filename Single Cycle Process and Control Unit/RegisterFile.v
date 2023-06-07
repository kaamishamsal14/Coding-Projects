`timescale 1ns / 1ps


module RegisterFile(BusA, BusB, BusW, RA, RB, RW, RegWr, Clk);
    output [63:0] BusA;
    output [63:0] BusB;
    input [63:0] BusW;
    input [4:0] RA; // A/B/W select are 5 bits wide to choose from 32 registers 
    input [4:0] RB;
    input [4:0] RW;
    input RegWr;
    input Clk;
	//make 32 64 bit registers
    reg [63:0] registers [31:0]; //64-bit register 32 of them
    
	//make sure RA/RB = 31 is 0, ternary operator works for this 
	//pass selected RA and RB to BusA and BusB
    assign #2 BusA = (RA == 31) ? 0 : registers[RA];
    assign #2 BusB = (RB == 31) ? 0 : registers[RB];
     
    always @ (negedge Clk) begin

        if(RegWr)begin
            registers[RW] <= #3	 BusW;
		end
    end
endmodule
