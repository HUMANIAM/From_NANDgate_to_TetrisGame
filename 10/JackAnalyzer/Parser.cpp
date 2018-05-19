#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <vector>
#include "Parser.h"
#include "Tokenizer.h"
using namespace std;

Parser::Parser()
{}

bool Parser::StartParsing()
{
    margin = 0;
    bool state = false;
    //get rid of tokens flag
    inputfile.getline(token,200,'\n');
    if(MoreTokens())
      state = CompileClass();
    if(!state)
        cout<<"there is error in this file when parsing it\n";
    return state;
}

void Parser::Margin(int m = 0)
{
    int i ;
   (m == 0)? i= margin : i = m;
   while(i-->0) outputfile<<"  ";
}

bool Parser::MoreTokens()
{
    if(!inputfile.eof())
    {
      inputfile.getline(token,200,'\n');
      string xmltoken = string (token);
      token_type[1].clear();

      //get the type of token
      size_t foundex = xmltoken.find_first_of("<");
      size_t foundin = xmltoken.find_first_of(">");
      if(foundex != string::npos && foundin != string::npos)
       token_type[0] = xmltoken.substr(foundex,foundin+1);
      else
       return false;

      //get the token itself
      foundex = xmltoken.find_first_of("<", foundin+1);
      if(foundex != string::npos && foundin != string::npos)
      {
        while(++foundin < foundex)
         if(xmltoken[foundin] != ' ')
          token_type[1].append(1,xmltoken[foundin]);
        return true;
      }
       else
        return false;

   return false;
    }
    else
     return false;
}

void Parser::WriteTerminal()
{
    //write the terminal into the xml file in the parser tree
   Margin();
   outputfile<< token<<endl;
   MoreTokens();
}

bool Parser::IsMachTokenType(string s)
{
    if(s == token_type[0])
    {
        WriteTerminal();
        return true;
    }
    return false;
}

bool Parser::IsMachToken(string s)
{
    if(s == token_type[1])
    {
        WriteTerminal();
        return true;
    }
    return false;
}

bool Parser::IsType(bool write)
{
    string tok = token_type[1];
    string toktype = token_type[0];
    bool f1 = ((tok == "char") || (tok == "int"));
    bool f2 = ((tok == "boolean") || (toktype == "<identifier>"));
    if((f1 || f2) && write)
    {
        WriteTerminal();
        return true;
    }
    else if(f1 || f2)
        return true;
    else
        return false;
}

bool Parser::IsCmFOr(string Or="")
{
    string type = token_type[1];
    bool f1 = ((type == "function") || (type == "method"));
    bool f2 = ((type == Or) || (type == "constructor"));
    return f1 || f2;
}

bool Parser::ClassVarDecRec()
{
    return (IsMachToken(",") && IsMachTokenType("<identifier>") && ClassVarDecRec())
           || (token_type[1] == ";");
}

bool Parser::CompileClassVarDec()
{
    if(token_type[1] == "static" || token_type[1] == "field")
     {
        //set margin
      int mymargin = margin;
       Margin(margin);
       margin++;
     //flag the grammer rule by classVarDec in the parse tree
       outputfile<<"<classVarDec>\n";

    //grammer rule of non terminal ClassVarDec
    bool state = (IsMachToken("static") || IsMachToken("field"))
                 && IsType(true) && IsMachTokenType("<identifier>") && ClassVarDecRec()&& IsMachToken(";")  ;
    if(state){
      margin = mymargin;
      Margin(mymargin);
      outputfile<<"</classVarDec>\n";
      return CompileClassVarDec();
    }
    return state;
    }
    else if(IsCmFOr("}"))
        return true;
    else
        return false;
}

bool Parser::ParamListRec()
{
    return (IsMachToken(",") && IsType(true) && IsMachTokenType("<identifier>") && ParamListRec())||(token_type[1] == ",");
}

bool Parser::CompileParameterList()
{
     //set margin
    int mymargin = margin;
    Margin(margin);
    margin++;
    outputfile<<"<parameterList>\n";
    //context free grammer of parameterlist
    bool state = (IsType(true) && IsMachTokenType("<identifier>") && ParamListRec()) || (token_type[1] == ")");

    if(state){
        margin = mymargin;
        Margin(mymargin);
        outputfile<<"</parameterList>\n";
    }
    return state;
}

bool Parser::IsFollowVarDec(string Or="")
{
    string tok = token_type[1];
    bool f1 = (tok == Or) || (tok == "if") || (tok == "let");
    bool f2 = (tok == "while") || (tok == "do") || (tok == "return");
    return f1 || f2;
}

bool Parser::VarDecRec()
{
    return (IsMachToken(",") && IsMachTokenType("<identifier>") && VarDecRec())
            ||(token_type[1] == ";");
}

bool Parser::CompileVarDec()
{
    if(token_type[1] == "var")
    {
        //set margin
    int mymargin = margin;
    Margin(margin);
    margin++;
    outputfile<<"<varDec>\n";
    bool state = IsMachToken("var") && IsType(true) && IsMachTokenType("<identifier>")
                  && VarDecRec()&& IsMachToken(";");
    if(state){
        margin = mymargin;
        Margin(mymargin);
        outputfile<<"</varDec>\n";
        return CompileVarDec();
    }
    return state;
    }
    else if(IsFollowVarDec("}"))
        return true;
    else
        return false;
}

bool Parser::IsKeywordConst(bool write)
{
   string type = token_type[1];
    bool f1 = ((type == "this") || (type == "true"));
    bool f2 = ((type == "null") || (type == "false"));
    if((f1 || f2) && write )
    {
        WriteTerminal();
        return true;
    }
    else if(f1 || f2)
        return true;
    else
        return false;
}

bool Parser::IsUnaryOp(bool write)
{
  string t = token_type[1];
  bool state = t == "-" || t == "~";
  if(write && state)
  {
      WriteTerminal();
      return true;
  }
  else if(state)
    return true;
  else
    return false;
}

bool Parser::ExpressionListRec()
{
  return (IsMachToken(",") && CompileExpression() && ExpressionListRec()) || (token_type[1] == ")");
}

bool Parser::CompileExpressionList()
{
    //set margin
    int mymargin = margin;
    Margin();
    margin++;
    outputfile<<"<expressionList>\n";
    //apply grammer of CompileExpressionList
    bool state = (token_type[1] == ")") || (CompileExpression() && ExpressionListRec()) ;

    if(state)
    {
        margin = mymargin;
        Margin(mymargin);
       outputfile<<"</expressionList>\n";
    }
    return state;
}

bool Parser::CompileSubroutineCall()
{
  return IsMachTokenType("<identifier>") && (( IsMachToken("(") && CompileExpressionList() && IsMachToken(")")) ||
        (IsMachToken(".") && IsMachTokenType("<identifier>")&&IsMachToken("(") &&CompileExpressionList() &&IsMachToken(")")));
}

bool Parser::CompileArrayExpression()
{
    return  IsMachToken("[") && CompileExpression() && IsMachToken("]");
}

bool Parser::CompileTerm()
{
    //set margin
    int mymargin = margin;
    Margin(margin);
    margin++;
    outputfile<<"<term>\n";
    //check first rules that don't begin with identifier
    bool check = IsMachTokenType("<integerConstant>")||IsMachTokenType("<stringConstant>")||IsKeywordConst(true)||
                  ( IsMachToken("(") && CompileExpression() && IsMachToken(")") ) || (IsUnaryOp(true) && CompileTerm());
    //if this condition of next if statement achieved this mean that the term begin with identifier and
    //it is a special case of this grammer
    //this is a trick. if subroutineCal fails that means two states one is that token may be not identifier and that
    //leads to fail array expression and varName expression. the anthor one means it is not subroutine call and
    //that means identifier has already written to the parser tree and we need check if the second token is
    //[ to apply array expression rule on it and if the second token isn't [ this means it is varname
    if(!check)
    {
        //check if grammer refers to subroutine
        check = CompileSubroutineCall();
        //if expression is not subroutine and identifier has already read we check the rest of grammer
        if(!check && (token_type[1] != "<identifier>") )
        {
          check = CompileArrayExpression();
          if(!check )
            check = true;
        }
    }
     if(check){
      margin = mymargin;
      Margin(mymargin);
      outputfile<<"</term>\n";
     }
     return check;
}

bool Parser::CompileOp(bool write)
{
    string ops = "+-*/|=";
    string tok = token_type[1];

    bool f1 = (ops.find(tok) != string::npos);
    bool f2 = (tok =="&amp;" || tok =="&lt;" || tok =="&gt;");
    if((f1 || f2) && write)
    {
        WriteTerminal();
        return true;
    }
    else if(f1 || f2)
        return true;
    else
        return false;
}


bool Parser::ExpressionRec()
{
    string t = token_type[1];
    return (CompileOp(true) && CompileTerm()) ||( t=="]"||t==";"||t==")" || t==",");
}


bool Parser::CompileExpression()
{
    //set margin
    int mymargin = margin;
    Margin(margin);
    margin++;
    outputfile<<"<expression>\n";
    bool state = CompileTerm() && ExpressionRec();

    if(state){
        margin = mymargin;
        Margin(mymargin);
        outputfile<<"</expression>\n";
    }
    return state;
}

bool Parser::IsStatement()
{
    string tok = token_type[1];
    bool f1 = (tok =="if" || tok =="while" || tok == "do") ;
    bool f2 = (tok == "let" || tok == "return");
	return f1||f2;

}
bool Parser::CompileReturnStat()
{
    if(token_type[1] == "return")
    {
        //set margin
      int mymargin = margin;
      Margin(margin);
      margin++;
      outputfile<<"<returnStatement>\n";
      bool state =  IsMachToken("return") && ((token_type[1] == ";") || CompileExpression() ) && IsMachToken(";");

       if(state){
        margin = mymargin;
        Margin(mymargin);
        outputfile<<"</returnStatement>\n";
       }
       return state;
    }
    else
        return false;
}

bool Parser::CompileIfWhileStat()
{
    if(token_type[1] == "while" || token_type[1] == "if")
    {
        //set margin
    string keywrd = token_type[1];
    int mymargin = margin;
     Margin(margin);
     margin++;
     outputfile<<"<" + token_type[1] + "Statement>\n";

     bool state = IsMachToken(token_type[1]) && IsMachToken("(") && CompileExpression()&&
                  IsMachToken(")") && IsMachToken("{") && CompileStatements() && IsMachToken("}") &&
                  ((IsMachToken("else")&& IsMachToken("{")&& CompileStatements()&& IsMachToken("}")) ||
                    (token_type[1]=="}" || IsStatement()));

     if(state){
        margin = mymargin;
        Margin(mymargin);
        outputfile<<"</" + keywrd + "Statement>\n";
     }
     return state;
    }
  else
    return false;
}
bool Parser::CompileDoStat()
{
     if(token_type[1] == "do")
     {
         //set margin
        int mymargin = margin;
       Margin(margin);
       margin++;
       outputfile<<"<doStatement>\n";
       bool state =  IsMachToken("do") && CompileSubroutineCall() && IsMachToken(";");

       if(state){
        margin = mymargin;
        Margin(mymargin);
        outputfile<<"</doStatement>\n";
       }
       return state;
     }
     else
        return false;
}
bool Parser::CompileLetStat()
{
 if(token_type[1] == "let")
 {
     //set margin
     int mymargin = margin;
     Margin(margin);
     margin++;
     outputfile<<"<letStatement>\n";
     bool state = IsMachToken("let") && IsMachTokenType("<identifier>") &&
                    ((IsMachToken("[") && CompileExpression() && IsMachToken("]")) || token_type[1] == "=") &&
                    IsMachToken("=") && CompileExpression() && IsMachToken(";");
    if(state){
        margin = mymargin;
        Margin(mymargin);
        outputfile<<"</letStatement>\n";
    }
    return state;
 }
 else
    return false;
}

bool Parser::Statement()
{
  return (token_type[1] == "}")||((CompileLetStat() || CompileDoStat() || CompileIfWhileStat()|| CompileReturnStat())&&Statement());
}

bool Parser::CompileStatements()
{
    if(IsFollowVarDec())
    {
        //set margin
      int mymargin = margin;
       Margin(margin);
       margin++;
       outputfile<<"<statements>\n";
       bool state = Statement();
       if(state){
        margin = mymargin;
        Margin(mymargin);
        outputfile<<"</statements>\n";
       }
       return state;
    }
    else if(token_type[1] == "}")
        return true;
    else
        return false;
}

bool Parser::SubroutineBody()
{
    //set margin
     int mymargin = margin;
      Margin();
      margin++;
    outputfile<<"<subroutineBody>\n";
    //apply grammer of subroutine Body
    bool state = IsMachToken("{") && CompileVarDec() && CompileStatements() && IsMachToken("}");

    if(state)
    {
        margin = mymargin;
        Margin(mymargin);
       outputfile<<"</subroutineBody>\n";
    }

    return state;
}

bool Parser::CompileSubroutineDec()
{
  if(IsCmFOr())
  {
      //set margin
      int mymargin = margin;
      Margin();
      margin++;
      //flag the grammer rule by classVarDec in the parse tree
       outputfile<<"<subroutineDec>\n";
       WriteTerminal();
      //grammer rule of non terminal ClassVarDec
      if(IsType(false) || token_type[1] == "void")
      {
          WriteTerminal();
          //rest of the grammer rule of subroutine
          bool state = IsMachTokenType("<identifier>") && IsMachToken("(")
                        && CompileParameterList() && IsMachToken(")") && SubroutineBody();
        //reset margin
        margin = mymargin;
        Margin(mymargin);
        outputfile<<"</subroutineDec>\n";
	if(state)
         return CompileSubroutineDec();
	else
	 return false;	

      }
      else
        return false;
  }
  else if(token_type[1] == "}")
    return true;
  else
    return false;
}

bool Parser::CompileClass()
{
    if(token_type[1] == "class" )
      //flag the class entry
      outputfile<<"<class>\n";
    //set margin
    margin++;
    //apply the rule of nonterminal class
    bool state = IsMachToken("class") && IsMachTokenType("<identifier>") && IsMachToken("{") &&
                 CompileClassVarDec() && CompileSubroutineDec() && IsMachToken("}");
    if(state)
        outputfile<<"</class>\n";
    return state;
}

