/* parser class contains
-Parsing(): read VM command by command and translate it into ASM code by calling CodeWriter class
-Split() and: help function to parsing
-Initialization():that initialize the VM commands lists by the correct values and initialize the assembly file
by some temporary locations
**/
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include "Parser.h"
#include "CodeWriter.h"

using namespace std;

void Parser::Parsing()
{
    while(!inputfile.eof())
      {
        char command[100];
        string str = "// ";
        components.clear();

          //read a vm command and split it into its parts
        inputfile.getline(command, 100, '\n');
        Split(command, str);

          //write the vm code into the asm file as comment
        if(components.size() != 0){
           outputfile<<str<<endl;
           nextaddress++;
           cw.CodeWritting();
        }
      }
}

void Parser::Split(char Command [], string& s)
{
    int i=0;
    string w;

    //stop reading when meeting \0 or / character
    while(Command[i] != '\0' && Command[i] !='/')
        {
           while(Command[i]!=' ' && Command[i] != '\0' && Command[i] !='/')
                w.append(1,Command[i++]);

           if(w.size() != 0){
             components.push_back(w);
             s = s + w + " ";
             w="";
           }

           while(Command[i] == ' ')
             i++;
        }
}

void Parser::Initialization()
{
      //Arthmatic logical operation
    arthim_logic_ops.push_back("or");
    arthim_logic_ops.push_back("and");
    arthim_logic_ops.push_back("gt");
    arthim_logic_ops.push_back("lt");
    arthim_logic_ops.push_back("add");
    arthim_logic_ops.push_back("sub");
    arthim_logic_ops.push_back("neg");
    arthim_logic_ops.push_back("eq");
    arthim_logic_ops.push_back("not");

    //memory segment operations
    memo_segm_ops.push_back("push");
    memo_segm_ops.push_back("pop");

    //branching operations
    brancing_ops.push_back("label");
    brancing_ops.push_back("if-goto");
    brancing_ops.push_back("goto");

    //function operations
    function_ops.push_back("function");
    function_ops.push_back("call");
    function_ops.push_back("return");
    Initasmfile();
}

void Parser::Initasmfile()
{
    //temporary locations
    outputfile<<"@address\n";
    outputfile<<"M = 0\n";
    outputfile<<"@frame\n";
    outputfile<<"M = 0\n";
    outputfile<<"@ret\n";
    outputfile<<"M = 0\n";
}

