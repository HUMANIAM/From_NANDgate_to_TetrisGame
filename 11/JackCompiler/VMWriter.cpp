#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "SymbolTable.h"
#include "VMWriter.h"

using namespace std;
int iflabel = 0;
int whilelabel = 0;
//constructor of VMWrite class
VMWriter::VMWriter(){}

//StartGeneration create the correct VM code of jack input
void VMWriter::StartGeneration()
{
    //grammer of class
    //class : 'class' ClassName '{' ClassVarDec* SubroutineDec* '}'
     Advance(false); Advance(false); Advance(false);  Advance(false);  Advance(true) ;
     AddEntriesToTables(); GenerateSubDec(); Advance(false);
}

void VMWriter::GenerateSubCall(string sub_obj_clss = "")
{
    /*
        subroutineCall : SubroutineName '(' expression ')' | (className | VarName)
                          '.' subroutineName '(' expressionList ')'
    */
    if(sub_obj_clss.size() == 0){
     sub_obj_clss = components[1];
     Advance(true);
    }
    int nargs = 0;

    //check if called subroutine in the current class or in other one
    if(components[1] == ".")
    {
       //get subroutine name
        Advance(true);
        string fname = components[1];
        //go to Generate expression list by stop at the tag <expressionList>
        Advance(false);  Advance(true);
        //call to object.subroutine(args)
        if(symtable.Indexof(sub_obj_clss) != -1)
        {
            int index = symtable.Indexof(sub_obj_clss);
            string kind = symtable.Kindof(sub_obj_clss);
            string type = symtable.Typeof(sub_obj_clss);
            //push reference to the object as the argument 0
            if(fname != "method")
            outputfile<<"push "<<kind<<" "<<index<<endl;
            //write the expression list
              GenerateExpressionList(nargs);

            //write the VM code
            outputfile<<"call "+type+"."+fname<<" "<<nargs+1<<endl;
        }
        //call to class.subroutine or osclass.subroutine
        else
        {
              // Generate expression list
           GenerateExpressionList(nargs);

             //write the vm code
           outputfile<<"call "+sub_obj_clss+"."+fname<<" "<<nargs<<endl;
        }
    }
    //call to this.subroutine
    else
    {
        outputfile<<"push pointer 0\n";
        //go to Generate expression list by stop at the tag <expressionList>
        Advance(true);
        GenerateExpressionList(nargs);

        //write the VM code
        outputfile<<"call "+classname+"."+sub_obj_clss<<" "<<nargs+1<<endl;
    }
}

//read terminals and non terminals in the XML parse tree
bool VMWriter::Advance(bool Split)
{
    //clear components to read new line from the parse tree
    components.clear();
    char token[200];
    //read new line
    if(!inputfile.eof())
    {
      inputfile.getline(token,200,'\n');
      //check if split the token parts or only read it
      if(!Split) return true;

      //else split the token parts into type and value
      string line = token;
      //remove the spaces at the beginning of the XMLtoken
      int i =0;
      while(line[i] == ' ') i++;
      line = line.substr(i);
     //read token type
      int found = line.find(">") + 1;
      components.push_back(line.substr(0,found));

      //read token value
      if (found != line.size()){
        line = line.substr(++found);
        found = line.find("<") - 1;
        components.push_back(line.substr(0,found));
      }
      return true;
    }
}

//add new entry to the symbol table
void VMWriter::AddEntriesToTables()
{
    //Grammar of ClassVarDec
 //ClassVarDec : ('static' | 'field') type VarName (',' VarName)* ';'
    //grammar of VarDec
//VarDec : 'var' type VarName (',' VarName)* ';'
 if(components[0] == "<varDec>" || components[0] == "<classVarDec>" )
 {
  string kind, type;
  //determine the kind of variable
  Advance(true);
  kind = components[1];
  //determine the type of variables
  Advance(true);
  type = components[1];

  //read variables one by one
  while(Advance(true) && components[1] != ";")
    if(components[1] != ",")
    {
        //add new entry to subroutine or class symbol table
        bool state = symtable.Define(components[1], type,kind);
        //defined before
        if(!state)
        {
           cout<<"this variable < "<< components[1] <<" > is defined before.\n";
           exit(0);
        }
    }
    Advance(false);
    Advance(true);
    AddEntriesToTables();
 }
}

//write VM function
void VMWriter::WriteFunction(string name, int nlocs)
{
    outputfile<<"function "<<classname<<"."<<name<<" "<<nlocs<<endl;
    string type = Classes_Methods[classname][name].type;
    if(type == "constructor")
    {
        //allocate memory to the new object
        int memsize = symtable.Varcount("field");
        outputfile<<"push constant "<<memsize<<endl;
        outputfile<<"call Memory.alloc 1\n";
        outputfile<<"pop pointer 0\n";
    }
    else if (type == "method")
    {
        //set the running object which is the method will operate on its data
        outputfile<<"push argument 0\n";
        outputfile<<"pop pointer 0\n";
    }
    else{}
}

//handling subroutine declaration by add local variables to the subroutine symbol table
void VMWriter::GenerateSubDec()
{
    //Grammar of SubroutineDec
    /*
    subroutineDec : ('constructor' | 'method' | 'function') ('void' | type)
                    SubroutineName '(' ParameterList ')'
                          SubroutineBody
    */
    if(components[0] == "<subroutineDec>" && Advance(true)){
    //build the symbol table of this subroutine
    //reset the subroutine symbol table
    symtable.StartSubroutine(components[1]);

    //read function name
    string fname;
    while(Advance(true) && components[0] != "<symbol>")
      fname = components[1];
    Advance(false);

    //Add arguments of this subroutine to the symbol table
    AddSubArguments(fname);         Advance(true);
    GenerateSubBody(fname);         Advance(true);
    GenerateSubDec();
    }
}

//subroutine body
void VMWriter::GenerateSubBody(string fname)
{
    /*grammar of subroutineBody
    subroutineBody : '{' varDec* Statements '}'
    */
    iflabel = whilelabel = 0;
    Advance(false);Advance(true);
    AddEntriesToTables();
    WriteFunction(fname,symtable.Varcount("var"));
    GenerateStatements(); Advance(false);
    Advance(false);
}
//statements
void VMWriter::GenerateStatements()
{
    /*
       grammar of statements
       Statements : statement*
    */
    Advance(true);  GenerateStatement();  Advance(false);
}
//statement
bool VMWriter::GenerateStatement()
{
    /*
        grammar of statement
        statement : letStatement | doStatement | whileStatement | returnStatement | ifStatement
    */
    return ( GenerateIf() | GenerateWhile() | GenerateReturn() | GenerateLet() | GenerateDo()) && GenerateStatement() ;
}

void VMWriter::AddSubArguments(string fname)
{
   /*
        grammar of parameterList
        parameterList : (( type varName)(',' varName)*) ';'
    */
    Advance(true);
    if(components[0] != "</parameterList>")
    {
        string argtype = components[1];    Advance(true);
        string argname = components[1];    Advance(true);
        symtable.Define(argname, argtype, "argument");

        while (components[0] != "</parameterList>" && Advance(true))
        {
            string argtype = components[1];    Advance(true);
            string argname = components[1];    Advance(true);
            symtable.Define(argname, argtype, "argument");
        }
    }
    Advance(false);
}

void VMWriter::Generateoperations(vector<string>& ops)
{
    for(size_t i=0; i<ops.size(); i++)
    {
        if(ops[i] == "+")
        {
            outputfile<<"add\n";
        }
        else if(ops[i] == "-")
        {
            outputfile<<"sub\n";
        }
        else if(ops[i] == "*")
        {
            outputfile<<"call Math.multiply 2\n";
        }
        else if(ops[i] == "/")
        {
           outputfile<<"call Math.divide 2\n";
        }
        else if(ops[i] == "&amp;")
        {
            outputfile<<"and\n";
        }
        else if(ops[i] == "&lt;")
        {
            outputfile<<"lt\n";
        }
        else if(ops[i] == "&gt;")
        {
            outputfile<<"gt\n";
        }
        else if(ops[i] == "=")
        {
            outputfile<<"eq\n";
        }
        else if(ops[i] == "|")
        {
            outputfile<<"or\n";
        }
        else{}
    }
}
void VMWriter::GenerateExpression()
{
    //from the free grammer of expression
    //expression : term (op term)*
    vector<string> operators ;
    Advance(false);
    GenerateTerm();

    if(components[0] != "</expression>")
    {
        while(components[0] != "</expression>")
        {
           //Generate op in (op term)*
            operators.push_back( components[1]);
            Advance(false);
            GenerateTerm();
        }
        if(operators.size() != 0)
         Generateoperations(operators);
    }
    Advance(true);
}

void VMWriter::GenerateTerm()
{
    //read the term
    Advance(true);
    string tokentype = components[0];
    string tokenvalue = components[1];

    if(tokentype == "<integerConstant>")
    {

        outputfile<<"push constant "<<tokenvalue<<endl;
        Advance(false);  Advance(true);
    }
    else if(tokentype == "<stringConstant>")
    {
        outputfile<<"push constant "<<tokenvalue.size()<<endl;
        outputfile<<"call String.new 1"<<endl;

        //append the character of string to the constant string created by os
        for(size_t i =0; i<tokenvalue.size(); i++)
        {
           outputfile<<"push constant "<<int(tokenvalue[i])<<endl;
           outputfile<<"call String.appendChar 2"<<endl;
        }

        Advance(false);  Advance(true);
    }
    else if(tokentype == "<keyword>" )
    {
      if(tokenvalue == "this")
      {
          outputfile<<"push pointer 0\n";
      }
      else if(tokenvalue == "true")
      {
          outputfile<<"push constant 0\n";
          outputfile<<"not\n";
      }
      else
      {
          outputfile<<"push constant 0\n";
      }
      Advance(false);  Advance(true);
    }
    else if(tokenvalue == "(" && Advance(true))
    {
       GenerateExpression();
       Advance(false);  Advance(true);
    }
    else if((tokenvalue == "~" || tokenvalue == "-") && Advance(false))
    {
        GenerateTerm();
        if(tokenvalue == "~")
           outputfile<<"not\n";
         else
           outputfile<<"neg\n";

         Advance(true);
    }
    else if(tokentype == "<identifier>" && Advance(true))
    {
        string nexttoken = components[1] ;
        //GenerateArrays
        if(nexttoken == "[")
        {
            GenerateArrays(tokenvalue, "SOURCE");
            Advance(true);
        }
        //GenerateSubCall
        else if (nexttoken == "." || nexttoken == "(")
        {
            GenerateSubCall(tokenvalue);
            Advance(false);  Advance(true);
        }
        //push variable
        else
        {
            int index = symtable.Indexof(tokenvalue);
            string kind = symtable.Kindof(tokenvalue);
            if(index == -1)
            {
                cout<<"this variable "<<tokenvalue<<" is not defined\n";
                exit(0);
            }
            outputfile<<"push "<<kind<<" "<<index<<endl;
            Advance(true);

        }
    }
    else{}
}
//Generate expression list of arguments
void VMWriter::GenerateExpressionList(int& nargs)
{
    //parameterList : ((type varname) ("," type varname)*)?
    Advance(true);
    if(components[0]!= "</expressionList>" )
    {
        nargs++;
        GenerateExpression();
        while(components[1] == "," && Advance(true) && nargs++)
         GenerateExpression();
    }
    Advance(false);
}

void VMWriter::GenerateArrays(string arr, string des_source)
{
    //arr[expression]
    //define the kind and index of the variable
    int index = symtable.Indexof(arr);
    string kind = symtable.Kindof(arr);

    if(index == -1)
    {
        cout<<"this array "<<arr<<" is not defined\n";
        exit(0);
    }

    Advance(true);
    GenerateExpression();
    Advance(true);
    outputfile<<"push "<<kind<<" "<<index<<endl;
    outputfile<<"add\n";

    if(des_source == "SOURCE")
    {
        outputfile<<"pop pointer 1\n";
        outputfile<<"push that 0\n";
    }
}

bool VMWriter::GenerateLet()
{
    if(components[0] == "<letStatement>"){
    //letStat : let && varname ('['expression']')? '=' expression ';'
    Advance(false);    Advance(true);
    string dest = components[1];
    Advance(true);
    string sym = components[1];
    if(sym == "[")
    {
      GenerateArrays(dest, "DEST");
      Advance(true);
      GenerateExpression();
      //keep the LHS result in temporary location
      outputfile<<"pop temp 0\n";
      //set pointer 1 to refer to the array location
      outputfile<<"pop pointer 1\n";
      //set LHS to RHS
      outputfile<<"push temp 0\n";
      outputfile<<"pop that 0\n";
    }
    else
    {
        Advance(true);
        GenerateExpression();
        //define the kind and index of the variable
        int index = symtable.Indexof(dest);
        string kind = symtable.Kindof(dest);

        if(index == -1)
        {
            cout<<"this variable "<<dest<<" is not defined\n";
            exit(0);
        }
        outputfile<<"pop "<<kind<<" "<<index<<endl;
    }
    Advance(false);
    Advance(true);
    return true;
    }
    return false;
}


bool VMWriter::GenerateDo()
{
    if (components[0] == "<doStatement>"){
       Advance(false);     Advance(true);
       GenerateSubCall("");
       Advance(false);     Advance(false);
       outputfile<<"pop temp 0\n";
       Advance(true);     return true;
    }
    return false;

}

bool VMWriter::GenerateIf()
{
    if(components[0] == "<ifStatement>")
    {
        int currentlabel = iflabel++;
        Advance(false); Advance(false); Advance(true);
        GenerateExpression();
        Advance(false); Advance(true);
        outputfile<<"if-goto IF_TRUE"<<currentlabel<<endl;
        outputfile<<"goto IF_FALSE"<<currentlabel<<endl;
        outputfile<<"label IF_TRUE"<<currentlabel<<endl;
        //Generate statements
        GenerateStatements(); Advance(true);

        //label to exceeds the else statements after execute if statements if condition is true
        if(components[0] != "</ifStatement>")
          outputfile<<"goto IF_END"<<currentlabel<<endl;
        outputfile<<"label IF_FALSE"<<currentlabel<<endl;

        //check if it has else part or not
        if(components[0] != "</ifStatement>")
        {
            Advance(false); Advance(true);
            //Generate statements in else part
            GenerateStatements();
            Advance(false);
            outputfile<<"label IF_END"<<currentlabel<<endl;
        }
        Advance(true);
        return true;
    }
    return false;
}

bool VMWriter::GenerateWhile()
{
    if(components[0] == "<whileStatement>")
    {
        int currentlabel = whilelabel++;
        outputfile<<"label WHILE_EXP"<<currentlabel<<endl;
        //calculate the condition
        Advance(false); Advance(false); Advance(true);
        GenerateExpression();
        outputfile<<"not\n";
        outputfile<<"if-goto WHILE_END"<<currentlabel<<endl;

        Advance(false); Advance(true);
        //Generate statements
        GenerateStatements();
        outputfile<<"goto WHILE_EXP"<<currentlabel<<endl;
        outputfile<<"label WHILE_END"<<currentlabel<<endl;
        Advance(false);    Advance(true);

        return true;
    }
    return false;
}

bool VMWriter::GenerateReturn()
{
    if(components[0] == "<returnStatement>")
    {
        Advance(false); Advance(true);
        if(components[0] == "<expression>")
            GenerateExpression();
        else
            outputfile<<"push constant 0\n";

        outputfile<<"return\n";
        Advance(false);     Advance(true);
        return true;
    }
    return false;
}
