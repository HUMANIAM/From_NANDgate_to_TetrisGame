/*
This is the core class that contains
CodeWritting(): call the proper Method according to the VM command type
-according to the type we call (function, branching, arth/logic, memory_segment) methods
-according to the type of the VM command we start to write the proper assembly code
//
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
#include "CodeWriter.h"
using namespace std;

void CodeWriter::CodeWritting()
{
    string oper = components[0];
  if(Find(oper, arthim_logic_ops))
  {
    ConvertArith_Logic();
  }
  else if(Find(oper, memo_segm_ops))
  {
    ConvertMemoSegment();
  }

  else if(Find(oper, function_ops))
  {
      ConvertFunction();
  }

  else if(Find(oper, brancing_ops))
  {
        ConvertBranching();
  }
  else{
        cout<<"in line "<<nextaddress-1<<" this command type isn't identified \n";
        exit(1);
  }
}

bool CodeWriter::Find(string oper, vector<string>& container)
{
    for(size_t i=0; i<container.size(); i++)
       if(oper == container[i])
            return true;

    return false;
}

void CodeWriter::ConvertArith_Logic()
{
    string oper = components[0];

    outputfile<<"@SP\n";
    outputfile<<"AM = M - 1\n";

    if(oper == "neg" || oper == "not")
    {
        if(oper == "neg")
           outputfile<<"M = -M\n";
        else
           outputfile<<"M = !M\n";
    }
    else
    {
        outputfile<<"D = M\n";
        outputfile<<"@SP\n";
        outputfile<<"AM = M - 1\n";
        CodeWriter::Arth_Log_TwoOperands(oper);
    }
    outputfile<<"@SP\n";
    outputfile<<"M = M + 1\n";
}

void CodeWriter::ConvertMemoSegment()
{
    if(components[0] == "push")
    {
        //specify the memory address where we need to push
        CodeWriter::ConvetAddress(components[1], components[2]);

        if(components[1] != "constant" && components[1] != "static")
          {
            string s = components[2];
            outputfile<<"@"+s<<endl;
            outputfile<<"AD = D + A\n";
            outputfile<<"D = M\n";
          }
        outputfile<<"@SP\n";
        outputfile<<"A = M\n";
        outputfile<<"M = D\n";
        outputfile<<"@SP\n";
        outputfile<<"M = M + 1\n";
    }

    else
    {
        if(components[1] != "static" && components[1] != "constant")
        {
           CodeWriter::ConvetAddress(components[1], components[2]);
           string i = components[2];
           outputfile<<"@"+i<<endl;
           outputfile<<"D = D + A\n";
           outputfile<<"@address\n";
           outputfile<<"M = D\n";
           outputfile<<"@SP\n";
           outputfile<<"AM = M -1\n";
           outputfile<<"D = M\n";
           outputfile<<"@address\n";
           outputfile<<"A = M\n";
           outputfile<<"M = D\n";
        }
        else if(components[1] == "static")
        {
           outputfile<<"@SP\n";
           outputfile<<"AM = M -1\n";
           outputfile<<"D = M\n";
           string s = vmfilename;
           s = s + "." + components[2];
           outputfile<<"@"+s<<endl;
           outputfile<<"M = D\n";
        }
        else{}
    }
}

void CodeWriter::ConvertBranching()
{
   if(components[0] == "label")
        WriteLabel();
    else if(components[0] == "goto")
        WriteGoto();
    else
        WriteIf();
}

void CodeWriter::ConvertFunction()
{
    if(components[0] == "function"){
       lastfn = components[1];
       WriteFunction();
    }

    else if(components[0] == "call")
        WriteCall();
    else
       WriteReturn();
}

void CodeWriter::Arth_Log_TwoOperands(string oper)
{
    if(oper == "add")
        outputfile<<"M = M + D\n";
    else if(oper == "sub")
        outputfile<<"M = M - D\n";
    else if(oper == "and")
        outputfile<<"M = D&M\n";
    else if(oper == "or")
        outputfile<<"M = D|M\n";
    else
    {
        string index= __int_to_string(operorder++);

        outputfile<<"D = M - D\n";
        outputfile<<"@YES"+index<<endl;

        if(oper == "gt")
            outputfile<<"D;JGT\n";

        else if (oper == "lt")
            outputfile<<"D;JLT\n";

        else if (oper == "eq")
            outputfile<<"D;JEQ\n";

        outputfile<<"@SP\n";
        outputfile<<"A = M\n";
        outputfile<<"M = 0\n";
        outputfile<<"@END"+index<<endl;
        outputfile<<"0;JMP\n";

        outputfile<<"(YES"+index+")"<<endl;
        outputfile<<"@SP\n";
        outputfile<<"A = M\n";
        outputfile<<"M = -1\n";
        outputfile<<"(END"+index+")"<<endl;
    }
}

string CodeWriter::__int_to_string(int Number)
{
    stringstream ss;
	ss << Number;
	return string(ss.str());
}

void CodeWriter::ConvetAddress(string segment, string i)
{
    if(segment == "local")
    {
        outputfile<<"@LCL\n";
        outputfile<<"D = M\n";
    }
    else if(segment == "constant")
    {
        outputfile<<"@"+i<<endl;
        outputfile<<"D = A\n";
    }
    else if(segment == "argument")
    {
        outputfile<<"@ARG\n";
        outputfile<<"D = M\n";
    }
    else if(segment == "temp")
    {
        string s = "5";
        outputfile<<"@"+s<<endl;
        outputfile<<"D = A\n";
    }
    else if(segment == "this")
    {
        outputfile<<"@THIS\n";
        outputfile<<"D = M\n";
    }
    else if(segment == "that")
    {
        outputfile<<"@THAT\n";
        outputfile<<"D = M\n";
    }
    else if(segment == "pointer")
    {
        string s = "3";
        outputfile<<"@"+s<<endl;
        outputfile<<"D = A\n";
    }
    else if(segment =="static")
    {
        string s = vmfilename + "." + i;
        outputfile<<"@"+s<<endl;
        outputfile<<"D = M\n";
    }
    else {
        cout<<"in line : "<<nextaddress-1<<" unkown memory segment\n";
        exit(1);
    }

}

void CodeWriter::WriteLabel()
{
    outputfile<< "(" + lastfn + "$" + components[1] + ")\n";
}

void CodeWriter::WriteGoto()
{
    outputfile<<"@" + lastfn + "$" + components[1]<<endl;
    outputfile<<"0;JMP\n";
}

void CodeWriter::WriteIf()
{
    //pop the topmost element in the stack
     outputfile<<"@SP\n";
     outputfile<<"AM = M - 1\n";
     outputfile<<"D = M\n";
     outputfile<<"@" + lastfn + "$" + components[1]<<endl;
     outputfile<<"D;JNE\n";
}

void CodeWriter::WriteCall()
{
    stringstream ss;
    ss << nextaddress;
    string nextadd = "RA$" + ss.str();

    //push the return address
    outputfile<<"// push return address\n";
    SaveValue(nextadd, 'c');

    //push LCL
    outputfile<<"// push LCL\n";
    SaveValue("LCL", 'p');

    //push ARG
    outputfile<<"// push ARG\n";
    SaveValue("ARG", 'p');

    //push THIS
    outputfile<<"// push THIS\n";
    SaveValue("THIS", 'p');

    //Push THAT
    outputfile<<"// push THAT\n";
    SaveValue("THAT", 'p');

    //ARG = SP - n - 5
    outputfile<<"// ARG = SP -n -5\n";
    //push Sp
    SaveValue("SP", 'p');
    //push n
    SaveValue(components[2], 'c');
    //push Sp - n
    components[0] = "sub";
    ConvertArith_Logic();
    //push 5
    SaveValue("5", 'c');
    //SP - n -5
    ConvertArith_Logic();
    //ARG = pop()
    SetPointer("ARG");

    //LCL = SP
    outputfile<<"//LCL = SP\n";
    outputfile<<"@SP\n";
    outputfile<<"D = M\n";
    outputfile<<"@LCL\n";
    outputfile<<"M = D\n";

    //goto f
      outputfile<<"@" + components[1]<<endl;
      outputfile<<"0;JMP\n";

    //(return address label)
      outputfile<<"("+nextadd+")\n";
}

void CodeWriter::WriteFunction()
{
  outputfile<<"(" + components[1] + ")\n";
  int i = atoi(components[2].c_str());
  components[0] = "push";
  components[1] = "constant";
  components[2] = "0";
  while(i-- > 0)
  {
      outputfile<<"// push constant 0\n";
      ConvertMemoSegment();
  }
}

void CodeWriter::WriteReturn()
{
    //Frame = LCL
    outputfile<<"// frame = LCL\n";
    outputfile<<"@LCL\n";
    outputfile<<"D = M\n";
    outputfile<<"@frame\n";
    outputfile<<"M = D\n";

    //RET = *(FRAME - 5)
    outputfile<<"// RET = *(FRAME - 5)\n";
    RestoreValue("ret", "5");

    // *ARG = pop()
    outputfile<<"// *ARG = pop()\n";
    outputfile<<"@SP\n";
    outputfile<<"AM = M - 1\n";
    outputfile<<"D = M\n";
    outputfile<<"@ARG\n";
    outputfile<<"A = M\n";
    outputfile<<"M = D\n";

    //SP = ARG + 1 ;
    outputfile<<"//SP = ARG + 1\n";
    outputfile<<"@ARG\n";
    outputfile<<"D = M + 1\n";
    outputfile<<"@SP\n";
    outputfile<<"M = D\n";

     //THAT = *(FRAME - 1)
     outputfile<<"// THAT = *(FRAME - 1)\n";
     RestoreValue("THAT", "1");

     //THIS = *(FRAME - 2)
     outputfile<<"// THIS = *(FRAME - 2)\n";
     RestoreValue("THIS", "2");

     //ARG = *(FRAME - 3)
     outputfile<<"// ARG = *(FRAME - 3)\n";
     RestoreValue("ARG", "3");

     //LCL = *(FRAME - 4)
     outputfile<<"// LCL = *(FRAME - 4)\n";
     RestoreValue("LCL", "4");

     //goto RET
     outputfile<<"@ret\n";
     outputfile<<"A = M\n";
     outputfile<<"0;JMP\n";

}

void CodeWriter::SaveValue(string p, char type)
{
    outputfile<<"@"+p<<endl;

    if(type == 'p')
    outputfile<<"D = M\n";
    else
      outputfile<<"D = A\n";

    outputfile<<"@SP\n";
    outputfile<<"A = M\n";
    outputfile<<"M = D\n";
    outputfile<<"@SP\n";
    outputfile<<"M = M + 1\n";
}

void CodeWriter::SetPointer(string p)
{
    outputfile<<"@SP\n";
    outputfile<<"AM = M -1\n";
    outputfile<<"D = M\n";
    outputfile<<"@"+p<<endl;
    outputfile<<"M = D\n";
}

void CodeWriter::RestoreValue(string p, string offset)
{
    outputfile<<"@frame\n";
    outputfile<<"D = M\n";
    outputfile<<"@"+offset<<endl;
    outputfile<<"A = D - A\n";
    outputfile<<"D = M\n";
    outputfile<<"@"+p<<endl;
    outputfile<<"M = D\n";
}
