// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// the program in high level
//while(true)
//read KBD  
//if KBD ==0 and screen==(111...11)
//clear the screen
//if KBD ==1 and screen == 0
//black the screen
//

//declare variable to iterate through rows and clomns i,j
@i
M=0

@SCREEN
D=A

@address
M=D

@8192
D=A

@sz
M=D

(KEYPRESSED)

//clear if KBD=0 SCREEN=-1 (11......11)
@KBD
D=M

@CHECKSCREEN    //if kbd == 0
D;JEQ

@FILLCON       //else if kbd == 1
0;JMP

(CHECKSCREEN)
@SCREEN         
D = M

@CLEARPIXEL    //if kbd==0 and screen == -1 clear the screen
D;JNE

(FILLCON)
//fill if not(screen)&kbd
 @SCREEN
D=!M

@KBD
D = D&M

@FILLPIXEL
D;JNE

@KEYPRESSED
0;JMP


//Make the screen black
(FILLPIXEL)
(LOOP1)

@i
D=M

@sz
D = M - D

@RESESTI
D;JEQ

@address
A=M
M=-1

@address
M = M+1

@i
M = M+1

@LOOP1
0;JMP



//Make the screen white
(CLEARPIXEL)
(LOOP)

@i
D=M

@sz
D = M - D

@RESESTI
D;JEQ

@address
A=M
M=0

@address
M = M+1

@i
M = M+1

@LOOP
0;JMP


(RESESTI)
@i
M=0

@SCREEN
D=A

@address
M=D
@KEYPRESSED
0;JMP