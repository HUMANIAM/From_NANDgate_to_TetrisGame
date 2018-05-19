@address
M = 0
@frame
M = 0
@ret
M = 0
//  This the assembly code of Sys.vm 

(Sys)
// function Sys.init 0 
(Sys.init)
// push constant 4000	 
@4000	
D = A
@SP
A = M
M = D
@SP
M = M + 1
// pop pointer 0 
@3
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
// push constant 5000 
@5000
D = A
@SP
A = M
M = D
@SP
M = M + 1
// pop pointer 1 
@3
D = A
@1
D = D + A
@address
M = D
@SP
AM = M -1
D = M
@address
A = M
M = D
// call Sys.main 0 
// push return address
@RA$6
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
// push SP
@SP
D = M
@SP
A = M
M = D
@SP
M = M + 1
//push n
@0
D = A
@SP
A = M
M = D
@SP
M = M + 1
//sub 
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M - D
@SP
M = M + 1
//push 5
@5
D = A
@SP
A = M
M = D
@SP
M = M + 1
//sub 
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M - D
@SP
M = M + 1
// ARG = pop()
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
@Sys.main
0;JMP
(RA$6)
// pop temp 1 
@5
D = A
@1
D = D + A
@address
M = D
@SP
AM = M -1
D = M
@address
A = M
M = D
// label LOOP 
(Sys.init$LOOP)
// goto LOOP 
@Sys.init$LOOP
0;JMP
// function Sys.main 5 
(Sys.main)
// push constant 0
@0
D = A
@SP
A = M
M = D
@SP
M = M + 1
// push constant 0
@0
D = A
@SP
A = M
M = D
@SP
M = M + 1
// push constant 0
@0
D = A
@SP
A = M
M = D
@SP
M = M + 1
// push constant 0
@0
D = A
@SP
A = M
M = D
@SP
M = M + 1
// push constant 0
@0
D = A
@SP
A = M
M = D
@SP
M = M + 1
// push constant 4001 
@4001
D = A
@SP
A = M
M = D
@SP
M = M + 1
// pop pointer 0 
@3
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
// push constant 5001 
@5001
D = A
@SP
A = M
M = D
@SP
M = M + 1
// pop pointer 1 
@3
D = A
@1
D = D + A
@address
M = D
@SP
AM = M -1
D = M
@address
A = M
M = D
// push constant 200 
@200
D = A
@SP
A = M
M = D
@SP
M = M + 1
// pop local 1 
@LCL
D = M
@1
D = D + A
@address
M = D
@SP
AM = M -1
D = M
@address
A = M
M = D
// push constant 40 
@40
D = A
@SP
A = M
M = D
@SP
M = M + 1
// pop local 2 
@LCL
D = M
@2
D = D + A
@address
M = D
@SP
AM = M -1
D = M
@address
A = M
M = D
// push constant 6 
@6
D = A
@SP
A = M
M = D
@SP
M = M + 1
// pop local 3 
@LCL
D = M
@3
D = D + A
@address
M = D
@SP
AM = M -1
D = M
@address
A = M
M = D
// push constant 123 
@123
D = A
@SP
A = M
M = D
@SP
M = M + 1
// call Sys.add12 1 
// push return address
@RA$22
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
// push SP
@SP
D = M
@SP
A = M
M = D
@SP
M = M + 1
//push n
@1
D = A
@SP
A = M
M = D
@SP
M = M + 1
//sub 
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M - D
@SP
M = M + 1
//push 5
@5
D = A
@SP
A = M
M = D
@SP
M = M + 1
//sub 
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M - D
@SP
M = M + 1
// ARG = pop()
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
@Sys.add12
0;JMP
(RA$22)
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
// push local 0 
@LCL
D = M
@0
AD = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push local 1 
@LCL
D = M
@1
AD = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push local 2 
@LCL
D = M
@2
AD = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push local 3 
@LCL
D = M
@3
AD = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push local 4 
@LCL
D = M
@4
AD = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1
// add 
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M + D
@SP
M = M + 1
// add 
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M + D
@SP
M = M + 1
// add 
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M + D
@SP
M = M + 1
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
// function Sys.add12 0 
(Sys.add12)
// push constant 4002 
@4002
D = A
@SP
A = M
M = D
@SP
M = M + 1
// pop pointer 0 
@3
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
// push constant 5002 
@5002
D = A
@SP
A = M
M = D
@SP
M = M + 1
// pop pointer 1 
@3
D = A
@1
D = D + A
@address
M = D
@SP
AM = M -1
D = M
@address
A = M
M = D
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
// push constant 12 
@12
D = A
@SP
A = M
M = D
@SP
M = M + 1
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


