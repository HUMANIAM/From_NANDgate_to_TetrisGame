@256
D = A
@SP
M = D
@address
M = 0
@frame
M = 0
@ret
M = 0
(PointerTest)
// push constant 3030 
@3030
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
// push constant 3040 
@3040
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
// push constant 32 
@32
D = A
@SP
A = M
M = D
@SP
M = M + 1
// pop this 2 
@THIS
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
// push constant 46 
@46
D = A
@SP
A = M
M = D
@SP
M = M + 1
// pop that 6 
@THAT
D = M
@6
D = D + A
@address
M = D
@SP
AM = M -1
D = M
@address
A = M
M = D
// push pointer 0 
@3
D = A
@0
AD = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1
// push pointer 1 
@3
D = A
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
// push this 2 
@THIS
D = M
@2
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
// push that 6 
@THAT
D = M
@6
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
