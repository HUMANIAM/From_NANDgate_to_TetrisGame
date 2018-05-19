#include <iostream>
#include <string>
#include <algorithm>
#include <regex>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <dirent.h>
#include <vector>
#include "Tokenizer.h"
#include "Parser.h"
using namespace std;

//definitions of the methods of the Tokenizer class
//constructor of Tokenizer class
Tokenizer::Tokenizer(char p [])
{
    strcpy(path, p);
    StartTokenization();
}

//Start Tokenize all files in the path if it is directory or tokenize it if file
void Tokenizer::StartTokenization()
{
    //this list hold all files needed to tokenized
    vector<string> files;
    // call ReadAllFiles if path is file files vector will has it is only
    //if path is directory files vector will has all jack files in it.
    ReadAllfiles(files);
    //Tokenize files file by file
    for(size_t i=0; i<files.size(); i++)
    {
        //open the correct output files and input files
        //file path without extension
        string Fpwithouext = Getoutfile(files[i]);
        string out = Fpwithouext + "T.xml";
        outputfile.close();
        inputfile.close();
        outputfile.open(out.c_str());
        inputfile.open(files[i].c_str());
        //tokenize the file
        Tokenize_File();
        //Parsing the file
        Parsing_File(Fpwithouext);
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
void Tokenizer::Parsing_File(string Fpwithouext)
{
    string in = Fpwithouext + "T.xml";
    string out = Fpwithouext + ".xml";
    outputfile.close();
    inputfile.close();
    outputfile.open(out.c_str());
    inputfile.open(in.c_str());
    Parser parsephase;
    parsephase.StartParsing();
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
        InsertToken(string(x));
        line = mat.suffix().str();
        break;
    }
}

//insert token into the xml file
void Tokenizer::InsertToken(string token)
{
    //check if it keyword
    if (regex_match (token, regex(keywords)))
       outputfile<< "<keyword> " + token +  " </keyword>\n";

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
