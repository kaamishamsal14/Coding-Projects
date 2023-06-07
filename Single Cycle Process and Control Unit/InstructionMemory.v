`timescale 1ns / 1ps
/*
 * Module: InstructionMemory
 *
 * Implements read-only instruction memory
 * 
 */
module InstructionMemory(Data, Address);
   parameter T_rd = 20;
   parameter MemSize = 40;
   
   output [31:0] Data;
   input [63:0]  Address;
   reg [31:0] 	 Data;
   
   /*
    * ECEN 350 Processor Test Functions
    * Texas A&M University
    */
   
   always @ (Address) begin

      case(Address)

	/* Test Program 1:
	 * Program loads constants from the data memory. Uses these constants to test
	 * the following instructions: LDUR, ORR, AND, CBZ, ADD, SUB, STUR and B.
	 * 
	 * Assembly code for test:
	 * 
	 * 0: LDUR X9, [XZR, 0x0]    //Load 1 into x9
	 * 4: LDUR X10, [XZR, 0x8]   //Load a into x10
	 * 8: LDUR X11, [XZR, 0x10]  //Load 5 into x11
	 * C: LDUR X12, [XZR, 0x18]  //Load big constant into x12
	 * 10: LDUR X13, [XZR, 0x20]  //load a 0 into X13
	 * 
	 * 14: ORR X10, X10, X11  //Create mask of 0xf
	 * 18: AND X12, X12, X10  //Mask off low order bits of big constant
	 * 
	 * loop:
	 * 1C: CBZ X12, end  //while X12 is not 0
	 * 20: ADD X13, X13, X9  //Increment counter in X13
	 * 24: SUB X12, X12, X9  //Decrement remainder of big constant in X12
	 * 28: B loop  //Repeat till X12 is 0
	 * 2C: STUR X13, [XZR, 0x20]  //store back the counter value into the memory location 0x20
	 */
	

	63'h000: Data = 32'hF84003E9; //11111000010 000000000 00 11111 01001
	63'h004: Data = 32'hF84083EA; //11111000010 000101000 00 11111 01010

	63'h008: Data = 32'hF84103EB;
	63'h00c: Data = 32'hF84183EC;
	63'h010: Data = 32'hF84203ED;
	63'h014: Data = 32'hAA0B014A;
	63'h018: Data = 32'h8A0A018C;//10001010000010100000000110001100
	//h45008049					 //01000101000000001000000001001001
	
	63'h01c: Data = 32'hB400008C;
	63'h020: Data = 32'h8B0901AD;
	63'h024: Data = 32'hCB09018C;
	63'h028: Data = 32'h17FFFFFD;  //11111000000
	63'h02c: Data = 32'hF80203ED;  //11111000000 000100000001111101101
	63'h030: Data = 32'hF84203ED;  //One last load to place stored value on memdbus for test checking.
								   //11111000010 00010000000 11111 01101

	/* Add code for your tests here */
	
	/*
		0x1234 5678 9abc def0 

		0x0000 0000 0000 def0 MOVZ X1, 0xdef0 LSL#0   110100101 00 1101111011110000 00001
		test ldur to get output of mem2reg LDUR x1, [xzr, 0x0] 11111000010 00000001 00 11111 00000 

		0x0000 0000 9abc 0000 MOVZ X2, 0x9abc, LSL#16 110100101 01 1001101010111100 00010
		0x0000 5678 0000 0000 MOVZ X3, 0x5678, LSL#32 110100101 10 0101011001111000 00011
		0x1234 0000 0000 0000 MOVZ X4, 0x1234, LSL#48 110100101 11 0001001000110100 00100
		
		MOVZ X5, 0x0, LSL#0 110100101 00 0000000000000000 00101
		
		ADD X9, X1, X2 10001011000 00001 000000 00010 01001		
		ADD X9, X5, X3 10001011000 00101 000000 00011 01001
		ADD X9, X5, X4 10001011000 00101 000000 00100 01001
		
		10001011000000010000000001001001
		
		X9 - 0x1234 5678 9abc def0 ->

		STUR X9, [xzr, 0x28] 11111000000 000101000 00 11111 01001
		LDUR x10, [xzr, 0x28] 11111000010 000101000 00 11111 01010

		LSL thru MOVZ function
		determined by instruction bits 22:21, 00->0 shift, 01->16 bits, 10->32 , 11->48
	*/

	63'h034: Data = 32'b110100101_00_1101111011110000_00001; //MOVZ X1, 0xdef0 LSL#0
	63'h038: Data = 32'b110100101_01_1001101010111100_00010; //MOVZ X2, 0x9abc, LSL#16
	63'h03c: Data = 32'b110100101_10_0101011001111000_00011; //MOVZ X3, 0x5678, LSL#32
	63'h040: Data = 32'b110100101_11_0001001000110100_00100; //MOVZ X4, 0x1234, LSL#48
	63'h044: Data = 32'b10001011000_00010_000000_00001_01001; //add
	63'h048: Data = 32'b10001011000_00011_000000_01001_01001; 
	63'h04c: Data = 32'b10001011000_00100_000000_01001_01001;
	63'h050: Data = 32'hF80283E9;//stur
	63'h054: Data = 32'hF84283EA;//ldur

	
	
	default: Data = 32'hXXXXXXXX;
      endcase
   end
endmodule
