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
// push constant 4 
@4
D = A
@SP
A = M
M = D
@SP
M = M + 1
// call Main.fibonacci 1 
// push return address
@RA$3
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
@1
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
@Main.fibonacci
0;JMP
(RA$3)
// label WHILE 
(Sys.init$WHILE)
// goto WHILE 
@Sys.init$WHILE
0;JMP


//   This the assembly code of Main.vm 

(Main)
// function Main.fibonacci 0 
(Main.fibonacci)
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
// push constant 2 
@2
D = A
@SP
A = M
M = D
@SP
M = M + 1
// lt 
@SP
AM = M - 1
D = M
@SP
AM = M - 1
D = M - D
@YES0
D;JLT
@SP
A = M
M = 0
@END0
0;JMP
(YES0)
@SP
A = M
M = -1
(END0)
@SP
M = M + 1
// if-goto IF_TRUE 
@SP
AM = M - 1
D = M
@Main.fibonacci$IF_TRUE
D;JNE
// goto IF_FALSE 
@Main.fibonacci$IF_FALSE
0;JMP
// label IF_TRUE 
(Main.fibonacci$IF_TRUE)
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
// label IF_FALSE 
(Main.fibonacci$IF_FALSE)
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
// push constant 2 
@2
D = A
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
// call Main.fibonacci 1 
// push return address
@RA$19
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
@1
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
@Main.fibonacci
0;JMP
(RA$19)
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
// push constant 1 
@1
D = A
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
// call Main.fibonacci 1 
// push return address
@RA$23
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
@1
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
@Main.fibonacci
0;JMP
(RA$23)
// add 
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M + D
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


