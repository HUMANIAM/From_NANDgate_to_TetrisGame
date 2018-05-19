#include <iostream>
#include <string>
#include <algorithm>
#include <regex>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <dirent.h>
#include <vector>
#include <map>
#include "Tokenizer.h"
#include "Parser.h"
#include "VMWriter.h"
using namespace std;

string classname;
//definitions of the methods of the Tokenizer class
//constructor of Tokenizer class
Tokenizer::Tokenizer(char p [])
{
    strcpy(path, p);
    Run();
}

//Start Tokenize all files in the path if it is directory or tokenize it if file
void Tokenizer::Run()
{
    //this list hold all files needed to tokenized
    vector<string> files;
    // call ReadAllFiles if path is file files vector will has it is only
    //if path is directory files vector will has all jack files in it.
    ReadAllfiles(files);
    //Tokenize files file by file
    Tokenize_Parsing_Generate(files, "tokenize");
    //Parsing files file by file
    Tokenize_Parsing_Generate(files, "parse");
    //generate the VM code file by file
    Tokenize_Parsing_Generate(files, "generate");
}
//get the name of the current class
string Tokenizer::GetClassName(string path)
{
    size_t i = path.size() - 1;
    string name= "";
    while(path[i] !='/')
     name.append(1,path[i--]);
    reverse(name.begin(),name.end());
    return name;
}
//tokenize file by file or parsing file by file
void Tokenizer::Tokenize_Parsing_Generate(vector<string>& files, string dowhat)
{
    string in, out, Fpwithouext;
    for(size_t i=0; i<files.size(); i++)
    {
         Fpwithouext = Getoutfile(files[i]);
         classname = GetClassName(Fpwithouext);
         //determine which phase we are in to start create the correct operations
         //so we get the path of the input file and the output file according to this current phase
         if(dowhat == "parse")
         {
             in = Fpwithouext + "T.xml";
             out = Fpwithouext + ".xml";
         }
         else if(dowhat == "generate")
         {
             in = Fpwithouext + ".xml";
             out = Fpwithouext + ".vm";
         }
        else
        {
             in = files[i];
             out = Fpwithouext + "T.xml";
        }
        outputfile.close();
        inputfile.close();
        outputfile.open(out.c_str());
        inputfile.open(in.c_str());
        if(dowhat == "parse")
        //parse the file
        Parsing_File();
        else if(dowhat == "tokenize")
         //tokenize the file
         Tokenize_File();
        else
        //generate the VM file
         Generating_File();
    }
}

//Tokenize file by file
void Tokenizer::Tokenize_File()
{
    char cline[200];
    string sline;
    size_t found;
    outputfile<<"<tokens>\n";

  // read the source file line by line and manage comments carefully
  while(!inputfile.eof())
  {
    inputfile.getline(cline, 200, '\n');
    sline = string(cline);

      //check if line has comment operator
    if( (found = sline.find("//")) != string::npos)
        //neglect the comment part
        Tokenize_Line(sline.substr(0, found));

    else if( (found = sline.find("/*")) != string::npos)
    {
       //neglect the comment part
       Tokenize_Line(sline.substr(0, found));
       //check if the same line has the closed operator of comment
       if(sline.find("*/") == string::npos)
          //read until reach the closed operator of the comment
          while(!inputfile.eof())
            {
              inputfile.getline(cline, 200, '\n');
              sline = string(cline);
              if( (found = sline.find("*/")) != string::npos)
                {
                  //neglect the sequence before the closed operator of the comment
                  Tokenize_Line(sline.substr(found+2));
                  break;
                }
            }
    }
    else
      Tokenize_Line(sline);
  }

  outputfile<<"</tokens>\n";
}

//Parsing the file by create the parse tree of it
void Tokenizer::Parsing_File()
{
    Parser parsephase;
    parsephase.StartParsing();
}

//generate vm code of file
void Tokenizer::Generating_File()
{
    VMWriter vmwriter;
    vmwriter.StartGeneration();
}
//Tokeinze line by line
void Tokenizer::Tokenize_Line(string line)
{
    //we need to extract tokens that match the regular expressions
  smatch mat;
  regex exp (regularExpr);

  //scan till match then advance then scan then match until reach the end of string
  while(regex_search (line, mat, exp))
    for (auto x:mat) {
        //pass line to get info if token function or constructor or method
        InsertToken(string(x), line);
        line = mat.suffix().str();
        break;
    }
}

//add subroutine properties to the current class (type, return value, name, number of arguments)
void Tokenizer::AddSubroutine(vector<string>& prop, int nargs, map<string,string>& parmlist)
{
    Classes_Methods[classname].insert(make_pair(prop[2], SubroutineProp(prop[0], prop[1], nargs, parmlist) ));
}
//get parameter list of a subroutine
int Tokenizer::GetParmaterList(string str, map<string,string>& parms)
{
  int i = 0;
  int len = str.size();
  while( i<len)
  {
    //get type of argument
    string type = "";
    while((str[i] == ' ' || str[i] == ',') && i<len ) i++;
    while(str[i] != ' ' && str[i] != ',' && i<len)
       type.append(1,str[i++]);

    //get the name of the argument
    string name = "";
    while((str[i] == ' ' || str[i] == ',') && i<len ) i++;
    while( str[i] != ' ' && str[i] != ',' && i<len)
       name.append(1,str[i++]);

    //add the argument to the map
    parms[name] = type;
  }
  return parms.size();
}

//get information about the subroutine in current class
void Tokenizer::SubroutineInfo(string type, string subroutinedec)
{
 int openparen = subroutinedec.find("(");
 int closeparen = subroutinedec.find(")");
 string stringtemp = subroutinedec.substr(0,openparen);
 //read type, name and return value of the subroutine in the vector in order
 vector<string> properties;
 int i = 0;
 int len = stringtemp.size();
 string part= "";
 while(i<len)
 {
    part = "";
    while(stringtemp[i] == ' ' && i<len) i++;
    while(stringtemp[i] != ' ' && i<len)
    part.append(1,stringtemp[i++]);
    if(part.size() != 0)
    properties.push_back(part);
 }
 //count number of arguments of the subroutine
 stringtemp = subroutinedec.substr(openparen+1, (closeparen-openparen-1));
//read the subroutine arguments and their number
 map<string, string> Parameterlist;
 int nargs = GetParmaterList(stringtemp,Parameterlist);

  //add this subroutine to the current keeping house of this class
  AddSubroutine(properties, nargs, Parameterlist);
}

//insert token into the xml file
void Tokenizer::InsertToken(string token, string xmlline)
{
    //check if it keyword
    if (regex_match (token, regex(keywords)))
    {
         outputfile<< "<keyword> " + token +  " </keyword>\n";
         //if it is new subroutine we need get its info
         if(token == "function" || token == "method" || token == "constructor")
            SubroutineInfo(token, xmlline);
    }


    else if (regex_match(token, regex(identifier)))
        outputfile<< "<identifier> " + token +  " </identifier>\n";

    else if (regex_match(token, regex(symbols)))
    {
        //map symbols used for XML markup
        if(token == ">")
            outputfile<< "<symbol> " + string("&gt;") +  " </symbol>\n";
        else if(token == "<")
            outputfile<< "<symbol> " + string("&lt;") +  " </symbol>\n";
        else if(token == "&")
            outputfile<< "<symbol> " + string("&amp;") +  " </symbol>\n";
        else
           outputfile<< "<symbol> " + token +  " </symbol>\n";
    }

    else if (regex_match(token, regex(stringConstant)))
        outputfile<< "<stringConstant> " + token.substr(1,token.size()-2) +  " </stringConstant>\n";

    else
        outputfile<< "<integerConstant> " + token +  " </integerConstant>\n";
}


//read all files in the directory
bool Tokenizer::ReadAllfiles(vector<string>& files)
{
    if(IsJackFile(string(path)))
        files.push_back(string(path));

    else
    {
        //open the directory
        DIR *dir = opendir(path);
        struct dirent *ent;

        if (dir != NULL)
        {
          //read file by file
          while ((ent = readdir (dir)) != NULL) {
            string file = string(ent->d_name);
            if(IsJackFile(file))
            files.push_back(string(path) + "/" + file);
          }
        }
      closedir (dir);
      return true;
    }
  return false;
}

//check if it is jack file or directory
bool Tokenizer::IsJackFile(string file)
{
    string extenstion = ".jack";
    int i=1;
    size_t t = file.size();

    if(t<6)
        return false;
    else
        while(i<6)
          if(file[t-i] == extenstion[5-i])
            i++;
          else
            return false;
    return true;
}


//get the path of file without extension
string Tokenizer::Getoutfile(string filevm)
{
    size_t found = filevm.find_last_of(".");
    return filevm.substr(0,found);
}
