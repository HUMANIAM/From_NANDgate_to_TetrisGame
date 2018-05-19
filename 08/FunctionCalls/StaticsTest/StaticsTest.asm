@address
M = 0
@frame
M = 0
@ret
M = 0
//     Bootstrap code
@256
D = A
@SP
M = D
//call Sys.init 0
// push return address
@RA$0
D = A
@SP
A = M
M = D
@SP
M = M + 1
// push LCL
@LCL
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push ARG
@ARG
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push THIS
@THIS
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push THAT
@THAT
D = M
@SP
A = M
M = D
@SP
M = M + 1
// ARG = SP -n -5
@SP
D = M
@SP
A = M
M = D
@SP
M = M + 1
@0
D = A
@SP
A = M
M = D
@SP
M = M + 1
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M - D
@SP
M = M + 1
@5
D = A
@SP
A = M
M = D
@SP
M = M + 1
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M - D
@SP
M = M + 1
@SP
AM = M -1
D = M
@ARG
M = D
//LCL = SP
@SP
D = M
@LCL
M = D
@Sys.init
0;JMP
(RA$0)
//    assembly code of Sys
(Sys)
// function Sys.init 0 
(Sys.init)
// push constant 6 
@6
D = A
@SP
A = M
M = D
@SP
M = M + 1
// push constant 8 
@8
D = A
@SP
A = M
M = D
@SP
M = M + 1
// call Class1.set 2 
// push return address
@RA$4
D = A
@SP
A = M
M = D
@SP
M = M + 1
// push LCL
@LCL
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push ARG
@ARG
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push THIS
@THIS
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push THAT
@THAT
D = M
@SP
A = M
M = D
@SP
M = M + 1
// ARG = SP -n -5
@SP
D = M
@SP
A = M
M = D
@SP
M = M + 1
@2
D = A
@SP
A = M
M = D
@SP
M = M + 1
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M - D
@SP
M = M + 1
@5
D = A
@SP
A = M
M = D
@SP
M = M + 1
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M - D
@SP
M = M + 1
@SP
AM = M -1
D = M
@ARG
M = D
//LCL = SP
@SP
D = M
@LCL
M = D
@Class1.set
0;JMP
(RA$4)
// pop temp 0 
@5
D = A
@0
D = D + A
@address
M = D
@SP
AM = M -1
D = M
@address
A = M
M = D
// push constant 23 
@23
D = A
@SP
A = M
M = D
@SP
M = M + 1
// push constant 15 
@15
D = A
@SP
A = M
M = D
@SP
M = M + 1
// call Class2.set 2 
// push return address
@RA$8
D = A
@SP
A = M
M = D
@SP
M = M + 1
// push LCL
@LCL
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push ARG
@ARG
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push THIS
@THIS
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push THAT
@THAT
D = M
@SP
A = M
M = D
@SP
M = M + 1
// ARG = SP -n -5
@SP
D = M
@SP
A = M
M = D
@SP
M = M + 1
@2
D = A
@SP
A = M
M = D
@SP
M = M + 1
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M - D
@SP
M = M + 1
@5
D = A
@SP
A = M
M = D
@SP
M = M + 1
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M - D
@SP
M = M + 1
@SP
AM = M -1
D = M
@ARG
M = D
//LCL = SP
@SP
D = M
@LCL
M = D
@Class2.set
0;JMP
(RA$8)
// pop temp 0 
@5
D = A
@0
D = D + A
@address
M = D
@SP
AM = M -1
D = M
@address
A = M
M = D
// call Class1.get 0 
// push return address
@RA$10
D = A
@SP
A = M
M = D
@SP
M = M + 1
// push LCL
@LCL
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push ARG
@ARG
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push THIS
@THIS
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push THAT
@THAT
D = M
@SP
A = M
M = D
@SP
M = M + 1
// ARG = SP -n -5
@SP
D = M
@SP
A = M
M = D
@SP
M = M + 1
@0
D = A
@SP
A = M
M = D
@SP
M = M + 1
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M - D
@SP
M = M + 1
@5
D = A
@SP
A = M
M = D
@SP
M = M + 1
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M - D
@SP
M = M + 1
@SP
AM = M -1
D = M
@ARG
M = D
//LCL = SP
@SP
D = M
@LCL
M = D
@Class1.get
0;JMP
(RA$10)
// call Class2.get 0 
// push return address
@RA$11
D = A
@SP
A = M
M = D
@SP
M = M + 1
// push LCL
@LCL
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push ARG
@ARG
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push THIS
@THIS
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push THAT
@THAT
D = M
@SP
A = M
M = D
@SP
M = M + 1
// ARG = SP -n -5
@SP
D = M
@SP
A = M
M = D
@SP
M = M + 1
@0
D = A
@SP
A = M
M = D
@SP
M = M + 1
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M - D
@SP
M = M + 1
@5
D = A
@SP
A = M
M = D
@SP
M = M + 1
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M - D
@SP
M = M + 1
@SP
AM = M -1
D = M
@ARG
M = D
//LCL = SP
@SP
D = M
@LCL
M = D
@Class2.get
0;JMP
(RA$11)
// label WHILE 
(Sys.init$WHILE)
// goto WHILE 
@Sys.init$WHILE
0;JMP


// This is the assembley code of Class1.vm
(Class1)
// function Class1.set 0 
(Class1.set)
// push argument 0 
@ARG
D = M
@0
AD = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1
// pop static 0 
@SP
AM = M -1
D = M
@Class1.0
M = D
// push argument 1 
@ARG
D = M
@1
AD = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1
// pop static 1 
@SP
AM = M -1
D = M
@Class1.1
M = D
// push constant 0 
@0
D = A
@SP
A = M
M = D
@SP
M = M + 1
// return 
// frame = LCL
@LCL
D = M
@frame
M = D
// RET = *(FRAME - 5)
@frame
D = M
@5
A = D - A
D = M
@ret
M = D
// *ARG = pop()
@SP
AM = M - 1
D = M
@ARG
A = M
M = D
//SP = ARG + 1
@ARG
D = M + 1
@SP
M = D
// THAT = *(FRAME - 1)
@frame
D = M
@1
A = D - A
D = M
@THAT
M = D
// THIS = *(FRAME - 2)
@frame
D = M
@2
A = D - A
D = M
@THIS
M = D
// ARG = *(FRAME - 3)
@frame
D = M
@3
A = D - A
D = M
@ARG
M = D
// LCL = *(FRAME - 4)
@frame
D = M
@4
A = D - A
D = M
@LCL
M = D
@ret
A = M
0;JMP
// function Class1.get 0 
(Class1.get)
// push static 0 
@Class1.0
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push static 1 
@Class1.1
D = M
@SP
A = M
M = D
@SP
M = M + 1
// sub 
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M - D
@SP
M = M + 1
// return 
// frame = LCL
@LCL
D = M
@frame
M = D
// RET = *(FRAME - 5)
@frame
D = M
@5
A = D - A
D = M
@ret
M = D
// *ARG = pop()
@SP
AM = M - 1
D = M
@ARG
A = M
M = D
//SP = ARG + 1
@ARG
D = M + 1
@SP
M = D
// THAT = *(FRAME - 1)
@frame
D = M
@1
A = D - A
D = M
@THAT
M = D
// THIS = *(FRAME - 2)
@frame
D = M
@2
A = D - A
D = M
@THIS
M = D
// ARG = *(FRAME - 3)
@frame
D = M
@3
A = D - A
D = M
@ARG
M = D
// LCL = *(FRAME - 4)
@frame
D = M
@4
A = D - A
D = M
@LCL
M = D
@ret
A = M
0;JMP


// This is the assembley code of Class2.vm
(Class2)
// function Class2.set 0 
(Class2.set)
// push argument 0 
@ARG
D = M
@0
AD = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1
// pop static 0 
@SP
AM = M -1
D = M
@Class2.0
M = D
// push argument 1 
@ARG
D = M
@1
AD = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1
// pop static 1 
@SP
AM = M -1
D = M
@Class2.1
M = D
// push constant 0 
@0
D = A
@SP
A = M
M = D
@SP
M = M + 1
// return 
// frame = LCL
@LCL
D = M
@frame
M = D
// RET = *(FRAME - 5)
@frame
D = M
@5
A = D - A
D = M
@ret
M = D
// *ARG = pop()
@SP
AM = M - 1
D = M
@ARG
A = M
M = D
//SP = ARG + 1
@ARG
D = M + 1
@SP
M = D
// THAT = *(FRAME - 1)
@frame
D = M
@1
A = D - A
D = M
@THAT
M = D
// THIS = *(FRAME - 2)
@frame
D = M
@2
A = D - A
D = M
@THIS
M = D
// ARG = *(FRAME - 3)
@frame
D = M
@3
A = D - A
D = M
@ARG
M = D
// LCL = *(FRAME - 4)
@frame
D = M
@4
A = D - A
D = M
@LCL
M = D
@ret
A = M
0;JMP
// function Class2.get 0 
(Class2.get)
// push static 0 
@Class2.0
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push static 1 
@Class2.1
D = M
@SP
A = M
M = D
@SP
M = M + 1
// sub 
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M - D
@SP
M = M + 1
// return 
// frame = LCL
@LCL
D = M
@frame
M = D
// RET = *(FRAME - 5)
@frame
D = M
@5
A = D - A
D = M
@ret
M = D
// *ARG = pop()
@SP
AM = M - 1
D = M
@ARG
A = M
M = D
//SP = ARG + 1
@ARG
D = M + 1
@SP
M = D
// THAT = *(FRAME - 1)
@frame
D = M
@1
A = D - A
D = M
@THAT
M = D
// THIS = *(FRAME - 2)
@frame
D = M
@2
A = D - A
D = M
@THIS
M = D
// ARG = *(FRAME - 3)
@frame
D = M
@3
A = D - A
D = M
@ARG
M = D
// LCL = *(FRAME - 4)
@frame
D = M
@4
A = D - A
D = M
@LCL
M = D
@ret
A = M
0;JMP


