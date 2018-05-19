@address
M = 0
@frame
M = 0
@ret
M = 0
// This is the assembley code of SimpleFunction.vm
(SimpleFunction)
// function SimpleFunction.test 2 
(SimpleFunction_SimpleFunction.test)
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
// add 
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M + D
@SP
M = M + 1
// not 
@SP
AM = M - 1
M = !M
@SP
M = M + 1
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
// add 
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M + D
@SP
M = M + 1
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


