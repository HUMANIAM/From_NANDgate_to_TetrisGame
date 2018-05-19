/* This VM Translator Take the VM code and translate it into hack assembly code
which will be taken by the assembler and is translated into binary code then at the
last this binary code will be run on the Hack computer platform. This VM translator
is Stack_based virtual machine where using the stack to perform operations by push/pop
commands.
**/
#include <string>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include<sstream>
#include<dirent.h>
#include "VMT.h"

using namespace std;

//This global variables used by all cpp files
vector<string> memo_segm_ops;            // Store memory segments operations push/pop
vector<string> arthim_logic_ops;         // Store ARTH/Logical operations
vector<string> function_ops;             // Store function commands (function, call, return)
vector<string> brancing_ops;             // Store branching commands (label, goto, if_goto)
vector<string> components;               // hold components of VM command
ifstream inputfile;                      // input file to read the VM code
ofstream outputfile;                     // output file to hold the assembly code
string lastfn;                           // used to name label according to their function
string vmfilename;                       // used to name static variables according their vm file such (static 0) >> FOO.0
char infile[200];                        // hold the name of input VM code file
char outfile[200];                       // hold the name of output assembly code file
int operorder;                           // trace the number of command in the VM code to create unique labels in call command

int nextaddress;

// main function
int main(int argc, char* argv[])
{
// Start the VM translator
VM_Translator vmtranslator(argv[1]);

return 0;
}
