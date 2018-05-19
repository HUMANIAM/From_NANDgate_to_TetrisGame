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
(SimpleAdd)
// push constant 7 
@7
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
// add 
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M + D
@SP
M = M + 1
