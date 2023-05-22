
//FLip Flop
module DFF(clk,in,out);
	input clk;
	input [3:0] in;
	output [3:0] out;
	reg [3:0] out;

	always @(posedge clk)
	out = in;
endmodule

//MUX
module Mux(channels,select,b);
input [15:0][3:0]channels;
input [3:0] select;
output [3:0] b;
wire [15:0][3:0] channels;
reg [3:0] b;
always @(*)
begin
 b=channels[select];
end
endmodule


//ADD operation
module ADDSUBER(inputA,inputB,opcode,outputC);
//---------------------------------------
input [3:0] inputA;
input [3:0] inputB;
input [3:0] opcode;
wire [3:0] inputA;
wire [3:0] inputB;
wire [3:0] opcode;
//---------------------------------------
output [3:0] outputC;
reg [3:0] outputC;
//---------------------------------------
always @(*)
begin
if(opcode[3])
 outputC=inputA+inputB;
 else
 outputC=inputA-inputB;
end

endmodule

//MULIPLY operation
module MUL(inputA,inputB,outputC);
input [3:0] inputA;
input [3:0] inputB;
output [3:0] outputC;
reg [3:0] outputC;

always@(*)
begin
	outputC=inputA*inputB;
end
endmodule
//DIVIDE operation
module DIV(inputA,inputB,outputC);
input [3:0] inputA;
input [3:0] inputB;
output [3:0] outputC;
reg [3:0] outputC;

always@(*)
begin
	outputC=inputA/inputB;
end
endmodule

//AND operation
module ANDER(inputA,inputB,outputC);
input [3:0] inputA;
input [3:0] inputB;
output [3:0] outputC;
reg [3:0] outputC;

always@(*)
begin
	outputC[0]=inputA[0]&inputB[0];
	outputC[1]=inputA[1]&inputB[1];
	outputC[2]=inputA[2]&inputB[2];
	outputC[3]=inputA[3]&inputB[3];
end
endmodule

//NAND operation
module NANDER(inputA,inputB,outputC);
input [3:0] inputA;
input [3:0] inputB;
output [3:0] outputC;
reg [3:0] outputC;

always@(*)
begin
	outputC[0]=!(inputA[0]&inputB[0]);
	outputC[1]=!(inputA[1]&inputB[1]);
	outputC[2]=!(inputA[2]&inputB[2]);
	outputC[3]=!(inputA[3]&inputB[3]);
end
endmodule
//OR operation
module ORER(inputA,inputB,outputC);
input [3:0] inputA;
input [3:0] inputB;
output [3:0] outputC;
reg [3:0] outputC;

always@(*)
begin
	outputC[0]=inputA[0]|inputB[0];
	outputC[1]=inputA[1]|inputB[1];
	outputC[2]=inputA[2]|inputB[2];
	outputC[3]=inputA[3]|inputB[3];
end
endmodule
//NOR operation
module NORER(inputA,inputB,outputC);
input [3:0] inputA;
input [3:0] inputB;
output [3:0] outputC;
reg [3:0] outputC;

always@(*)
begin
	outputC[0]=!(inputA[0]|inputB[0]);
	outputC[1]=!(inputA[1]|inputB[1]);
	outputC[2]=!(inputA[2]|inputB[2]);
	outputC[3]=!(inputA[3]|inputB[3]);
end
endmodule
//XOR operation
module XORER(inputA,inputB,outputC);
input [3:0] inputA;
input [3:0] inputB;
output [3:0] outputC;
reg [3:0] outputC;

always@(*)
begin
	outputC[0]=(inputA[0]|inputB[0])&!(inputA[0]&inputB[0]);
	outputC[1]=(inputA[1]|inputB[1])&!(inputA[1]&inputB[1]);
	outputC[2]=(inputA[2]|inputB[2])&!(inputA[2]&inputB[2]);
	outputC[3]=(inputA[3]|inputB[3])&!(inputA[3]&inputB[3]);
end
endmodule
//XNOR operation
module XNORER(inputA,inputB,outputC);
input [3:0] inputA;
input [3:0] inputB;
output [3:0] outputC;
reg [3:0] outputC;

always@(*)
begin
	outputC[0]=!((inputA[0]|inputB[0])&!(inputA[0]&inputB[0]));
	outputC[1]=!((inputA[1]|inputB[1])&!(inputA[1]&inputB[1]));
	outputC[2]=!((inputA[2]|inputB[2])&!(inputA[2]&inputB[2]));
	outputC[3]=!((inputA[3]|inputB[3])&!(inputA[3]&inputB[3]));
end
endmodule
//NOT operation
module NOTER(inputA,outputC);
input [3:0] inputA;
output [3:0] outputC;
reg [3:0] outputC;

always@(*)
begin
	outputC[0]=!(inputA[0]);
	outputC[1]=!(inputA[1]);
	outputC[2]=!(inputA[2]);
	outputC[3]=!(inputA[3]);
end
endmodule
//Accumulator Register


//Breadboard
module breadboard(clk,A,C,opcode);
//----------------------------------
input clk; 
input rst;
input [3:0] A;
input [3:0] opcode;
wire clk;
wire rst;
wire [3:0] A;
wire [3:0] B;
wire [3:0] opcode;
//----------------------------------
output [3:0] C;
reg [3:0] C;
//----------------------------------

wire [15:0][3:0]channels;
wire [3:0] b;
wire [3:0] outputADDSUB;
wire [3:0] outputMULT;
wire [3:0] outputDIV;
wire [3:0] outputAND;
wire [3:0] outputNAND;
wire [3:0] outputOR;
wire [3:0] outputNOR;
wire [3:0] outputXOR;
wire [3:0] outputXNOR;
wire [3:0] outputNOT;
wire error;


reg [3:0] regA;
reg [3:0] regB;
reg err;

reg  [3:0] next;
wire [3:0] cur;

Mux mux1(channels,opcode,b);
ADDSUBER add(regB,regA,opcode,outputADDSUB);
MUL mult(regA,regB,outputMULT);
DIV divide(regB,regA,outputDIV);
ANDER and1(regA,regB,outputAND);
NANDER nand1(regA,regB,outputNAND);
ORER or1(regA,regB,outputOR);
NORER nor1(regA,regB,outputNOR);
XORER xor1(regA,regB,outputXOR);
XNORER xnor1(regA,regB,outputXNOR);
NOTER not1(regB,outputNOT);

DFF ACC1 (clk,next,cur);


assign channels[0]=cur;//NO-OP
assign channels[1]=outputADDSUB;
assign channels[2]=outputADDSUB;
assign channels[3]=outputMULT;
assign channels[4]=outputDIV;
assign channels[5]=0;
assign channels[6]=0;
assign channels[7]=outputNOT;
assign channels[8]=outputAND;
assign channels[9]=outputOR;
assign channels[10]=outputXOR;
assign channels[11]=outputNAND;
assign channels[12]=outputNOR;
assign channels[13]=outputXNOR;
assign channels[14]=A;
assign channels[15]=0;

always @(*)
begin
 regA=A;
 regB=cur;
 err=error;

 assign C=b;
 assign next=b;
end

endmodule


//TEST BENCH
module testbench();

//Local Variables
   reg clk;
   reg rst;
   reg [3:0] inputA;
   wire [3:0] outputC;
   reg [3:0] opcode;
   reg [15:0] count;

// create breadboard
breadboard bb8(clk,inputA,outputC,opcode);


   //CLOCK
   initial begin //Start Clock Thread
     forever //While TRUE
        begin //Do Clock Procedural
          clk=0; //square wave is low
          #5; //half a wave is 5 time units
          clk=1;//square wave is high
          #5; //half a wave is 5 time units
        end
    end



    initial begin //Start Output Thread
  $display("   |      |      |       |Binary  |Decimal |      |       |");
  $display("   |      |Binary|Decimal|previous|previous|Binary|Decimal|");  
  $display("clk|opcode|input |input  |value   |value   |output|output |");  
  $display("===+======+======+=======+========+========+======+=======+");  
  #4;//Offset to make sure data is not on the exact low-to-high positive edge.
	forever
         begin
		 	$display("%3b|%6b|%6b|%7d|%8b|%8d|%6b|%7d|", //Display values when clock is low
		clk,
		opcode,
		inputA,
		inputA,
		bb8.regB,
		bb8.regB,
		bb8.b,
		bb8.b,
		);
		
	#4;

		 	$display("%3b|%6b|%6b|%7d|%8b|%8d|%6b|%7d|", //Display values when clock is low
		clk,
		opcode,
		inputA,
		inputA,
		bb8.regB,
		bb8.regB,
		bb8.b,
		bb8.b,
		);
		 #2;
		 end
	end
//STIMULOUS
	initial begin//Start Stimulous Thread
	#6;	
	//---------------------------------
	inputA=4'b0000;
	opcode=4'b1111;//RESET
	#10; 
	//---------------------------------
	inputA=4'b0101;
	opcode=4'b1110;//LOAD
	#10
	//---------------------------------	
	inputA=4'b0000;
	opcode=4'b0000;//NO OP
	#10;
	//---------------------------------	
	inputA=4'b0011;
	opcode=4'b0011;//MUL
	#10;
	//---------------------------------	
	inputA=4'b0010;
	opcode=4'b0100;//DIV
	#10;
	//---------------------------------	
	inputA=4'b1000;
	opcode=4'b0001;//ADD
	#10;
	//---------------------------------	
	inputA=4'b0001;
	opcode=4'b0010;//SUB
	#10;
	//---------------------------------	
	inputA=4'b0000;
	opcode=4'b1111;//RESET
	#10;
	//---------------------------------	
	inputA=4'b0000;
	opcode=4'b0111;//NOT
	#10;
	//---------------------------------	
	inputA=4'b1010;
	opcode=4'b1101;//XNOR
	#10;
	//---------------------------------	
	inputA=4'b1100;
	opcode=4'b1011;//NAND
	#10;
	//---------------------------------1
	inputA=4'b0010;
	opcode=4'b1010;//XOR
	#10;
	//---------------------------------	
	inputA=4'b1110;
	opcode=4'b1100;//NOR
	#10;
	//---------------------------------	
	inputA=4'b1111;
	opcode=4'b1001;//OR
	#10;
	//---------------------------------	
	inputA=4'b0001;
	opcode=4'b1000;//AND
	#10;
	//---------------------------------	
	inputA=4'b0000;
	opcode=4'b1111;//RESET
	#10;

	$finish;
	end

endmodule